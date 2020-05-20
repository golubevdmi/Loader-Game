#include <Model/GridModel.h>

#include <Model/StepCommand.h>

#include <QUndoStack>
#include <QUndoCommand>
#include <QDebug>

GridModel::GridModel(QObject *parent)
    : QAbstractTableModel(parent)
    , _gridGenerator(new TestGridGenerator)
    , _pStack(new QUndoStack(this))
    , _pUndoCmd(nullptr)
    , _width(0)
    , _height(0)
    , _nSteps(0)
{}

GridModel::~GridModel()
{
    if (_pUndoCmd)
        delete _pUndoCmd;
}

void GridModel::reset()
{
    beginResetModel();

    _currentGrid = _beginGrid;

    endResetModel();

    if (_pStack)
        _pStack->clear();
    if (_pUndoCmd)
    {
        delete _pUndoCmd;
        _pUndoCmd = nullptr;
    }
    _nSteps = 0;
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
    return _height;
}

int GridModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return _width;
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
    Q_ASSERT(_gridGenerator);

    _width = width;
    _height = height;

    _gridGenerator->setWidth(_width);
    _gridGenerator->setHeight(_height);

    _gridGenerator->init();
    _gridGenerator->generate();

    // Update grid
    beginResetModel();
    _beginGrid = _gridGenerator->getGrid();
    reset();
    endResetModel();

    emit grid_changed();
    emit loader_index_changed(getLoaderPlayerIndex());
}

void GridModel::grid5x5()
{
    Q_ASSERT(_gridGenerator);
    _gridGenerator->setLoaderPlayers(1);
    _gridGenerator->setCargos(2);
    _gridGenerator->setCargosDestination(2);
    _gridGenerator->setBarriers(3);
    createGrid(5, 5);
}

void GridModel::grid10x10()
{
    Q_ASSERT(_gridGenerator);
    _gridGenerator->setLoaderPlayers(1);
    _gridGenerator->setCargos(2);
    _gridGenerator->setCargosDestination(2);
    _gridGenerator->setBarriers(3);
    createGrid(10, 10);
}

void GridModel::grid15x15()
{
    Q_ASSERT(_gridGenerator);
    _gridGenerator->setLoaderPlayers(1);
    _gridGenerator->setCargos(5);
    _gridGenerator->setCargosDestination(5);
    _gridGenerator->setBarriers(15);
    createGrid(15, 15);
}

bool GridModel::moveUp()
{
    if (checkWin())
    {
        emit game_win();
        return false;
    }
    QModelIndex indexLoader = getLoaderPlayerIndex();
    if (indexLoader.isValid())
    {
        QModelIndex indexToMove = this->index(indexLoader.row() - 1, indexLoader.column(), QModelIndex());
        if (indexToMove.isValid())
        {
            if (move(indexLoader, indexToMove))
            {
                qDebug() << "move up";
                movedComplete();
                return true;
            }
        }
    }
    return false;
}

bool GridModel::moveDown()
{
    if (checkWin())
    {
        emit game_win();
        return false;
    }
    QModelIndex indexLoader = getLoaderPlayerIndex();
    if (indexLoader.isValid())
    {
        QModelIndex indexToMove = this->index(indexLoader.row() + 1, indexLoader.column(), QModelIndex());
        if (indexToMove.isValid())
        {
            if (move(indexLoader, indexToMove))
            {
                qDebug() << "move down";
                movedComplete();
                return true;
            }
        }
    }
    return false;
}

bool GridModel::moveLeft()
{
    if (checkWin())
    {
        emit game_win();
        return false;
    }
    QModelIndex indexLoader = getLoaderPlayerIndex();
    if (indexLoader.isValid())
    {
        QModelIndex indexToMove = this->index(indexLoader.row(), indexLoader.column() - 1, QModelIndex());
        if (indexToMove.isValid())
        {
            if (move(indexLoader, indexToMove))
            {
                qDebug() << "move left";
                movedComplete();
                return true;
            }
        }
    }
    return false;
}

bool GridModel::moveRight()
{
    if (checkWin())
    {
        emit game_win();
        return false;
    }
    QModelIndex indexLoader = getLoaderPlayerIndex();
    if (indexLoader.isValid())
    {
        QModelIndex indexToMove = this->index(indexLoader.row(), indexLoader.column() + 1, QModelIndex());
        if (indexToMove.isValid())
        {
            if (move(indexLoader, indexToMove))
            {
                qDebug() << "move right";
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
    ++_nSteps;
}

void GridModel::addIndexForCommand(const QModelIndex &index, const QVariant &oldValue, const QVariant &newValue)
{
    if (!_pUndoCmd)
    {
        _pUndoCmd = new StepCommand(this);
    }
    auto pCustomCmd = dynamic_cast<StepCommand*>(_pUndoCmd);
    if (pCustomCmd)
        pCustomCmd->addIndex(index, oldValue, newValue);
}

void GridModel::saveStep()
{
    if (_pStack && _pUndoCmd)
    {
        _pStack->push(_pUndoCmd);
        _pUndoCmd = nullptr;
    }
}

bool GridModel::undo()
{
    if (_pStack && _pStack->index() > 0)
    {
        qDebug() << "stack index: " + QString::number(_pStack->index())
                 << ", nSteps: " + QString::number(_nSteps)
                 << " - undo";
        _pStack->undo();
        emit cargos_left(calcCargosLeft());
        return true;
    }
    return false;
}

bool GridModel::redo()
{
    if (_pStack && _pStack->index() < _nSteps)
    {
        qDebug() << "stack index: " + QString::number(_pStack->index())
                 << ", nSteps: " + QString::number(_nSteps)
                 << " - redo";
        _pStack->redo();
        emit cargos_left(calcCargosLeft());
        return true;
    }
    return false;
}

size_t GridModel::calcCargosLeft() const
{
    size_t nCargos = std::count(_currentGrid.begin(), _currentGrid.end(), FieldValue::CargoDestination);
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
        _currentGrid[index.row() * _height + index.column()] = value.toInt();
    }
}

int GridModel::getFieldsCargos() const
{
    if (_gridGenerator)
        return _gridGenerator->getCargos();
    return -1;
}

int GridModel::getFieldsCargosDestination() const
{
    if (_gridGenerator)
        return _gridGenerator->getCargosDestination();
    return -1;
}

int GridModel::getFieldsBarriers() const
{
    if (_gridGenerator)
        return _gridGenerator->getBarriers();
    return -1;
}

QModelIndex GridModel::getLoaderPlayerIndex()
{
    auto it = std::find(_currentGrid.begin(), _currentGrid.end(), FieldValue::LoaderPlayer);
    if (it != _currentGrid.end())
    {
        auto index = std::distance(_currentGrid.begin(), it);
        return createIndex(index / _height, index % _height);
    }
    return QModelIndex();
}

QVariant GridModel::getValue(const QModelIndex &index) const
{
    if (index.isValid())
        return QVariant(_currentGrid[index.row() * _height + index.column()]);
    return QVariant();
}

QVariant GridModel::getBeginValue(const QModelIndex &index) const
{
    if (index.isValid())
        return QVariant(_beginGrid[index.row() * _height + index.column()]);
    return QVariant();
}
