#include <MVC/GridModel.h>

#include <QFile>
#include <QTextStream>
#include <QRect>
#include <QDebug>

GridModel::GridModel(QObject *parent)
    : QAbstractTableModel(parent)
    , _gridGenerator(new RandomGridGenerator)
    , _width(0)
    , _height(0)
{}

void GridModel::reset()
{
    _currentGrid = _beginGrid;
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

    switch (role)
    {
    case Qt::DisplayRole:
    case Qt::EditRole:
        return QVariant(_currentGrid[index.row() * _height + index.column()]);
    }
    return QVariant();
}

bool GridModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    if (!calcCargosLeft())
    {
        emit game_win();
        return false;
    }

    int indexInt = index.row() * _height + index.column();

    switch (role)
    {
    case Qt::DisplayRole:
    case Qt::EditRole:
    {
        switch (_currentGrid[indexInt])
        {
        case FieldValue::Barrier:
            return false;
        default:
            if (value.toInt() == FieldValue::Empty && _beginGrid[indexInt] == FieldValue::CargoDestination)
                _currentGrid[indexInt] = FieldValue::CargoDestination;
            else
                _currentGrid[indexInt] = value.toInt();
            break;
        }
        break;
    }
    default:
        return false;
    }

    if (_beginGrid[indexInt] == FieldValue::CargoDestination && _currentGrid[indexInt] == FieldValue::Cargo)
    {
        emit cargo_delivered();
        qDebug() << "cargo delivered";

        int nCargos = calcCargosLeft();
        emit cargos_left(nCargos);
        if (!nCargos)
            emit game_win();
    }
    emit dataChanged(index, index, {role});
    return true;
}

Qt::ItemFlags GridModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags nReturn;
    nReturn |= Qt::ItemIsEnabled;
    if (index.isValid())
    {
        //nReturn |= Qt::ItemIsEditable;
        if (index.model()->data(index, Qt::DisplayRole).toInt() == FieldValue::Loader)
            nReturn |= Qt::ItemIsSelectable;
    }
    return nReturn;
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
    _currentGrid = _beginGrid = _gridGenerator->getGrid();
    endResetModel();

    // Find loader
    auto it = std::find(_currentGrid.begin(), _currentGrid.end(), FieldValue::Loader);
    auto index = std::distance(_currentGrid.begin(), it);

    emit grid_changed();
    emit loader_index_changed(createIndex(index / _height, index % _height));
    qDebug() << _currentGrid.size() << ": " << _width << "--" << _height
             << ". selected: " << index << " -- " << index / _height << ", " << index % _height;
}

void GridModel::grid5x5()
{
    Q_ASSERT(_gridGenerator);
    _gridGenerator->setLoaders(1);
    _gridGenerator->setCargos(2);
    _gridGenerator->setCargosDestination(2);
    _gridGenerator->setBarriers(3);
    createGrid(5, 5);
}

void GridModel::grid10x10()
{
    Q_ASSERT(_gridGenerator);
    _gridGenerator->setLoaders(1);
    _gridGenerator->setCargos(2);
    _gridGenerator->setCargosDestination(2);
    _gridGenerator->setBarriers(3);
    createGrid(10, 10);
}

void GridModel::grid15x15()
{
    Q_ASSERT(_gridGenerator);
    _gridGenerator->setLoaders(1);
    _gridGenerator->setCargos(5);
    _gridGenerator->setCargosDestination(5);
    _gridGenerator->setBarriers(15);
    createGrid(15, 15);
}

size_t GridModel::calcCargosLeft()
{
    size_t nCargos = std::count(_currentGrid.begin(), _currentGrid.end(), FieldValue::CargoDestination);
    return nCargos;
}








