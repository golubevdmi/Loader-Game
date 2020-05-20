#include <Model/GridModel.h>

#include <Model/StepCommand.h>

#include <QUndoStack>
#include <QUndoCommand>
#include <QDebug>

GridModel::GridModel(QObject *parent)
    : QAbstractTableModel(parent)
    , m_pGridGenerator(new TestGridGenerator)
    , m_pStack(new QUndoStack(this))
    , m_pUndoCmd(nullptr)
    , m_width(0)
    , m_height(0)
    , m_nSteps(0)
{}

GridModel::~GridModel()
{
    if (m_pUndoCmd)
        delete m_pUndoCmd;
}

void GridModel::reset()
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
    m_nSteps = 0;
}

QModelIndex GridModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();
    return createIndex(row, column);
}

int GridModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_height;
}

int GridModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_width;
}

QVariant GridModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    QVariant value = getValue(index);
    switch (role)
    {
    case FieldValue::Empty:
    case FieldValue::LoaderPlayer:
    case FieldValue::Cargo:
    case FieldValue::CargoDestination:
    case FieldValue::Barrier:
        return value.toInt() == role ? true : false;
    case Qt::DisplayRole:
    case Qt::EditRole:
        return value;
    }
    return QVariant();
}

bool GridModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    beginResetModel();

    switch (role)
    {
    case Qt::DisplayRole:
    case Qt::EditRole:
        setValue(index, value);
        emit dataChanged(index, index, {role});
        break;
    default:
        return false;
    }

    endResetModel();

    return true;
}

Qt::ItemFlags GridModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    Qt::ItemFlags nReturn;
    nReturn |= Qt::ItemIsEnabled;
    return nReturn;
}

QHash<int, QByteArray> GridModel::roleNames() const
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

void GridModel::createGrid(int width, int height)
{
    Q_ASSERT(width > 0 && height > 0);
    Q_ASSERT(m_pGridGenerator);

    m_width = width;
    m_height = height;

    m_pGridGenerator->setWidth(m_width);
    m_pGridGenerator->setHeight(m_height);

    m_pGridGenerator->init();
    m_pGridGenerator->generate();

    // Update grid
    beginResetModel();
    m_beginGrid = m_pGridGenerator->getGrid();
    reset();
    endResetModel();

    emit grid_changed();
    emit loader_index_changed(getLoaderPlayerIndex());
}

void GridModel::grid5x5()
{
    Q_ASSERT(m_pGridGenerator);
    m_pGridGenerator->setLoaderPlayers(1);
    m_pGridGenerator->setCargos(2);
    m_pGridGenerator->setCargosDestination(2);
    m_pGridGenerator->setBarriers(3);
    createGrid(5, 5);
}

void GridModel::grid10x10()
{
    Q_ASSERT(m_pGridGenerator);
    m_pGridGenerator->setLoaderPlayers(1);
    m_pGridGenerator->setCargos(2);
    m_pGridGenerator->setCargosDestination(2);
    m_pGridGenerator->setBarriers(3);
    createGrid(10, 10);
}

void GridModel::grid15x15()
{
    Q_ASSERT(m_pGridGenerator);
    m_pGridGenerator->setLoaderPlayers(1);
    m_pGridGenerator->setCargos(5);
    m_pGridGenerator->setCargosDestination(5);
    m_pGridGenerator->setBarriers(15);
    createGrid(15, 15);
}

bool GridModel::moveUp()
{
    bool ret = moveLoader(-1, 0);
    if (ret)
        qDebug() << "move up";
    return ret;
}

bool GridModel::moveDown()
{
    bool ret = moveLoader(1, 0);
    if (ret)
        qDebug() << "move down";
    return ret;
}

bool GridModel::moveLeft()
{
    bool ret = moveLoader(0, -1);
    if (ret)
        qDebug() << "move left";
    return ret;
}

bool GridModel::moveRight()
{
    bool ret = moveLoader(0, 1);
    if (ret)
        qDebug() << "move right";
    return ret;
}

bool GridModel::moveLoader(int rowOffset, int columnOffset)
{
    if (checkWin())
    {
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

bool GridModel::move(const QModelIndex &indexBegin, const QModelIndex &indexEnd)
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
        if (indexBegin.data().toInt() == FieldValue::Cargo)
            return false;
        // Cargo destination cell
        int rowOffset = indexEnd.row() - indexBegin.row();
        int colOffset = indexEnd.column() - indexBegin.column();
        QModelIndex indexCargoDst = this->index(indexEnd.row() + rowOffset, indexEnd.column() + colOffset, QModelIndex());
        if (move(indexEnd, indexCargoDst))
        {
            if (getBeginValue(indexCargoDst).toInt() == FieldValue::CargoDestination)
            {
                qDebug() << "cargo delivered";
                emit cargo_delivered();
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
    setData(indexEnd, indexBegin.data());

    // Fill old pos
    QVariant valueBegin = indexBegin.data();
    switch (getBeginValue(indexBegin).toInt())
    {
    case FieldValue::CargoDestination:
        addIndexForCommand(indexBegin, indexBegin.data(), QVariant(FieldValue::CargoDestination));
        setData(indexBegin, QVariant(FieldValue::CargoDestination));
        break;
    default:
        addIndexForCommand(indexBegin, indexBegin.data(), QVariant(FieldValue::Empty));
        setData(indexBegin, QVariant(FieldValue::Empty));
        break;
    }
    return true;
}

void GridModel::movedComplete()
{
    if (checkWin())
    {
        qDebug() << "game win";
        emit game_win();
    }
    emit cargos_left(calcCargosLeft());
    saveStep();
    ++m_nSteps;
}

void GridModel::addIndexForCommand(const QModelIndex &index, const QVariant &oldValue, const QVariant &newValue)
{
    if (!m_pUndoCmd)
    {
        m_pUndoCmd = new StepCommand(this);
    }
    auto pCustomCmd = dynamic_cast<StepCommand*>(m_pUndoCmd);
    if (pCustomCmd)
        pCustomCmd->addIndex(index, oldValue, newValue);
}

void GridModel::saveStep()
{
    if (m_pStack && m_pUndoCmd)
    {
        m_pStack->push(m_pUndoCmd);
        m_pUndoCmd = nullptr;
    }
}

bool GridModel::undo()
{
    if (m_pStack && m_pStack->index() > 0)
    {
        qDebug() << "stack index: " + QString::number(m_pStack->index())
                 << ", nSteps: " + QString::number(m_nSteps)
                 << " - undo";
        m_pStack->undo();
        emit cargos_left(calcCargosLeft());
        return true;
    }
    return false;
}

bool GridModel::redo()
{
    if (m_pStack && m_pStack->index() < m_nSteps)
    {
        qDebug() << "stack index: " + QString::number(m_pStack->index())
                 << ", nSteps: " + QString::number(m_nSteps)
                 << " - redo";
        m_pStack->redo();
        emit cargos_left(calcCargosLeft());
        return true;
    }
    return false;
}

size_t GridModel::calcCargosLeft() const
{
    size_t nCargos = std::count(m_currentGrid.begin(), m_currentGrid.end(), FieldValue::CargoDestination);
    return nCargos;
}

bool GridModel::checkWin()
{
    int nCargos = calcCargosLeft();
    return !nCargos;
}

void GridModel::setValue(const QModelIndex &index, QVariant value)
{
    if (index.isValid() && !value.isNull())
    {
        m_currentGrid[index.row() * m_height + index.column()] = value.toInt();
    }
}

int GridModel::getFieldsCargos() const
{
    if (m_pGridGenerator)
        return m_pGridGenerator->getCargos();
    return -1;
}

int GridModel::getFieldsCargosDestination() const
{
    if (m_pGridGenerator)
        return m_pGridGenerator->getCargosDestination();
    return -1;
}

int GridModel::getFieldsBarriers() const
{
    if (m_pGridGenerator)
        return m_pGridGenerator->getBarriers();
    return -1;
}

QModelIndex GridModel::getLoaderPlayerIndex()
{
    auto it = std::find(m_currentGrid.begin(), m_currentGrid.end(), FieldValue::LoaderPlayer);
    if (it != m_currentGrid.end())
    {
        auto index = std::distance(m_currentGrid.begin(), it);
        return createIndex(index / m_height, index % m_height);
    }
    return QModelIndex();
}

QVariant GridModel::getValue(const QModelIndex &index) const
{
    if (index.isValid())
        return QVariant(m_currentGrid[index.row() * m_height + index.column()]);
    return QVariant();
}

QVariant GridModel::getBeginValue(const QModelIndex &index) const
{
    if (index.isValid())
        return QVariant(m_beginGrid[index.row() * m_height + index.column()]);
    return QVariant();
}
