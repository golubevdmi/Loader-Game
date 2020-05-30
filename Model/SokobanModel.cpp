#include <Model/SokobanModel.h>

#include <Model/StepCommand.h>

#include <QUndoStack>
#include <QUndoCommand>
#include <QDebug>

SokobanModel::SokobanModel(QObject *parent)
    : QAbstractTableModel(parent)
    , m_pGridGenerator(new GridFromFile("Z:/Sokoban/mazes.json"))
    , m_pStack(new QUndoStack(this))
    , m_pUndoCmd(nullptr)
    , m_currStep(0)
    , m_nSteps(0)
    , m_nMoves(0)
{
    if (m_pGridGenerator)
        m_pGridGenerator->init();
}

SokobanModel::~SokobanModel()
{
    if (m_pUndoCmd)
        delete m_pUndoCmd;
}

void SokobanModel::reset()
{
    beginResetModel();

    m_currentGrid = m_beginGrid;

    endResetModel();

    if (m_pStack)
        m_pStack->clear();
    if (m_pUndoCmd)
    {
        delete m_pUndoCmd;
        m_pUndoCmd = nullptr;
    }
    m_currStep = 0;
    m_nSteps = 0;
    m_nMoves = 0;
    emit move_changed();
    emit grid_changed();
    emit cargos_left(cargosLeft());
}

QModelIndex SokobanModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();
    return createIndex(row, column);
}

int SokobanModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_pGridGenerator->getHeight();
}

int SokobanModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_pGridGenerator->getWidth();
}

QVariant SokobanModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    QVariant value = getValue(index);
    QVariant valueBegin = getBeginValue(index);
    switch (role)
    {
    case FieldValue::CargoDestination:
        return valueBegin.toInt() == role ? true : false;
    case FieldValue::Empty:
    case FieldValue::LoaderPlayer:
    case FieldValue::Cargo:
    case FieldValue::Barrier:
        return value.toInt() == role ? true : false;
    case Qt::DisplayRole:
    case Qt::EditRole:
        return value;
    }
    return QVariant();
}

bool SokobanModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    switch (role)
    {
    case Qt::DisplayRole:
    case Qt::EditRole:
        setValue(index, value);
        emit data_changed_custom(index.row(), index.column(), index.data());
        emit dataChanged(index, index, {role});
        break;
    default:
        return false;
    }

    return true;
}

Qt::ItemFlags SokobanModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    Qt::ItemFlags nReturn;
    nReturn |= Qt::ItemIsEnabled;
    return nReturn;
}

QHash<int, QByteArray> SokobanModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "display";
    roles[Qt::EditRole] = "edit";
    roles[FieldValue::Empty] = "Empty";
    roles[FieldValue::LoaderPlayer] = "LoaderPlayer";
    roles[FieldValue::Cargo] = "Cargo";
    roles[FieldValue::CargoDestination] = "CargoDestination";
    roles[FieldValue::Barrier] = "Barrier";
    return roles;
}

bool SokobanModel::loadLevel(int lvlNumber)
{
    if (m_pGridGenerator)
    {
        if (m_pGridGenerator->loadLevel(lvlNumber))
        {
            m_beginGrid = m_pGridGenerator->getGrid();
            reset();
            return true;
        }
    }
    return false;
}

// Read next grid
bool SokobanModel::loadNextLvl()
{
    if (m_pGridGenerator)
    {
        int currLvl = m_pGridGenerator->getCurrentLvl();
        return loadLevel(++currLvl);
    }
    return false;
}

// Read previous grid
bool SokobanModel::loadPrevLvl()
{
    if (m_pGridGenerator)
    {
        int currLvl = m_pGridGenerator->getCurrentLvl();
        return loadLevel(--currLvl);
    }
    return false;
}

bool SokobanModel::moveUp()
{
    bool ret = moveLoader(-1, 0);
    if (ret)
    {
        emit moved_up();
        qDebug() << "move up";
    }
    return ret;
}

bool SokobanModel::moveDown()
{
    bool ret = moveLoader(1, 0);
    if (ret)
    {
        moved_down();
        qDebug() << "move down";
    }
    return ret;
}

bool SokobanModel::moveLeft()
{
    bool ret = moveLoader(0, -1);
    if (ret)
    {
        moved_left();
        qDebug() << "move left";
    }
    return ret;
}

bool SokobanModel::moveRight()
{
    bool ret = moveLoader(0, 1);
    if (ret)
    {
        moved_right();
        qDebug() << "move right";
    }
    return ret;
}

bool SokobanModel::moveLoader(int rowOffset, int columnOffset)
{
    if (checkWin())
    {
        qDebug() << "move false: lvl complete";
        emit game_win();
        return false;
    }
    QModelIndex index = getLoaderPlayerIndex();
    if (index.isValid())
    {
        QModelIndex indexToMove = this->index(index.row() + rowOffset,
                                              index.column() + columnOffset, QModelIndex());
        if (indexToMove.isValid())
        {
            if (move(index, indexToMove))
            {
                movedComplete();
                return true;
            }
        }
    }
    return false;
}

// Game logic of displacement of objects
bool SokobanModel::move(const QModelIndex &indexBegin, const QModelIndex &indexEnd)
{
    if (!indexBegin.isValid() || !indexEnd.isValid())
        return false;

    // Check end pos
    switch (indexEnd.data().toInt())
    {
    case FieldValue::Barrier:
        return false;
    case FieldValue::Cargo:
    {
        // Cargo destination cell
        if (indexBegin.data().toInt() == FieldValue::Cargo)
            return false;
        int rowOffset = indexEnd.row() - indexBegin.row();
        int colOffset = indexEnd.column() - indexBegin.column();
        QModelIndex indexCargoDst = this->index(indexEnd.row() + rowOffset, indexEnd.column() + colOffset, QModelIndex());
        if (move(indexEnd, indexCargoDst))
        {
            if (getBeginValue(indexCargoDst).toInt() == FieldValue::CargoDestination)
            {
                emit delivered();
                qDebug() << "delivered";
            }
        }
        else
        {
            return false;
        }
        break;
    }
    }

    // Fill begin pos
    addIndexForCommand(indexEnd, indexEnd.data(), indexBegin.data());
    //setData(indexEnd, indexBegin.data()); // uncommented, if not add to QUndoStack

    // Fill old pos
    QVariant valueBegin = indexBegin.data();
    switch (getBeginValue(indexBegin).toInt())
    {
    case FieldValue::CargoDestination:
        addIndexForCommand(indexBegin, indexBegin.data(), QVariant(FieldValue::CargoDestination));
        //setData(indexBegin, QVariant(FieldValue::CargoDestination)); // uncommented, if not add to QUndoStack
        break;
    default:
        addIndexForCommand(indexBegin, indexBegin.data(), QVariant(FieldValue::Empty));
        //setData(indexBegin, QVariant(FieldValue::Empty)); // uncommented, if not add to QUndoStack
        break;
    }
    return true;
}

// If the move player is successful
void SokobanModel::movedComplete()
{
    saveStep();
    if (checkWin())
    {
        qDebug() << "lvl complete";
        emit game_win();
    }
    emit cargos_left(cargosLeft());
    m_nSteps = ++m_currStep;
    ++m_nMoves;
    emit move_changed();
}

// Add move to undoCommand
void SokobanModel::addIndexForCommand(const QModelIndex &index, const QVariant &oldValue, const QVariant &newValue)
{
    if (!m_pUndoCmd)
    {
        m_pUndoCmd = new StepCommand(this);
    }
    auto pCustomCmd = dynamic_cast<StepCommand*>(m_pUndoCmd);
    if (pCustomCmd)
        pCustomCmd->addIndex(index, oldValue, newValue);
}

// Add UndoCommand to stack
void SokobanModel::saveStep()
{
    if (m_pStack && m_pUndoCmd)
    {
        m_pStack->push(m_pUndoCmd);
        m_pUndoCmd = nullptr;
    }
}

bool SokobanModel::undo()
{
    if (m_pStack && m_pStack->index() > 0)
    {
        m_pStack->undo();
        --m_currStep;
        cmdComplete();
        emit cargos_left(cargosLeft());
        return true;
    }
    return false;
}

bool SokobanModel::redo()
{
    if (m_pStack && m_pStack->index() < m_nSteps)
    {
        m_pStack->redo();
        ++m_currStep;
        cmdComplete();
        emit cargos_left(cargosLeft());
        return true;
    }
    return false;
}

// If undo/redo is successful
void SokobanModel::cmdComplete()
{
    qDebug() << "stack index: " + QString::number(m_pStack->index())
             << ", nSteps: " + QString::number(m_nSteps);
    if (checkWin())
    {
        qDebug() << "lvl complete";
        emit game_win();
    }
    ++m_nMoves;
    emit move_changed();
}

int SokobanModel::cargos() const
{
    if (m_pGridGenerator)
    {
        return m_pGridGenerator->getNumberOfElements(FieldValue::Cargo);
    }
    return -1;
}

int SokobanModel::cargosLeft() const
{
    int nCargos = 0;
    auto it = m_beginGrid.begin();
    while (it != m_beginGrid.end())
    {
        it = std::find(it, m_beginGrid.end(), FieldValue::CargoDestination);
        if (it != m_beginGrid.end())
        {
            auto index = std::distance(m_beginGrid.begin(), it);
            if (m_currentGrid[index] != FieldValue::Cargo)
                ++nCargos;
            ++it;
        }
    }
    return nCargos;
}

int SokobanModel::step() const
{
    return m_currStep;
}

int SokobanModel::nMoves() const
{
    return m_nMoves;
}

int SokobanModel::level() const
{
    if (m_pGridGenerator)
    {
        return m_pGridGenerator->getCurrentLvl();
    }
    return -1;
}

bool SokobanModel::checkWin()
{
    int nCargos = cargosLeft();
    return !nCargos;
}

// Set value to current grid
void SokobanModel::setValue(const QModelIndex &index, QVariant value)
{
    if (index.isValid() && !value.isNull())
    {
        m_currentGrid[index.row() * columnCount() + index.column()] = value.toInt();
    }
}

QModelIndex SokobanModel::getLoaderPlayerIndex()
{
    auto it = std::find(m_currentGrid.begin(), m_currentGrid.end(), FieldValue::LoaderPlayer);
    if (it != m_currentGrid.end())
    {
        auto index = std::distance(m_currentGrid.begin(), it);
        return createIndex(index / columnCount(), index % columnCount());
    }
    return QModelIndex();
}

// Get value from current grid
QVariant SokobanModel::getValue(const QModelIndex &index) const
{
    if (index.isValid())
        return QVariant(m_currentGrid[index.row() * columnCount() + index.column()]);
    return QVariant();
}

// Get value from begin grid
QVariant SokobanModel::getBeginValue(const QModelIndex &index) const
{
    if (index.isValid())
        return QVariant(m_beginGrid[index.row() * columnCount() + index.column()]);
    return QVariant();
}
