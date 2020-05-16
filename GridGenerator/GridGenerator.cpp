#include <GridGenerator/GridGenerator.h>


GridGenerator::GridGenerator()
    : _width(0)
    , _height(0)
    , _nLoaderPlayer(1)
    , _nCargo(1)
    , _nCargoDst(1)
    , _nBarrier(0)
{}

// Initial GridGenerator on width and height
void GridGenerator::init()
{
    _grid.clear();
    _grid.resize(_width * _height);
    std::fill(_grid.begin(), _grid.end(), FieldValue::Empty);
}

// Generate GridGenerator
void GridGenerator::generate()
{
    Q_ASSERT(_nLoaderPlayer > 0 && _nCargo > 0 && _nCargoDst > 0 && _nBarrier >= 0);
    Q_ASSERT(size_grid());
    Q_ASSERT(size_elements() < size_grid());

    fill(FieldValue::LoaderPlayer, _nLoaderPlayer, _grid);
    fill(FieldValue::Cargo, _nCargo, _grid);
    fill(FieldValue::CargoDestination, _nCargoDst, _grid);
    fill(FieldValue::Barrier, _nBarrier, _grid);
}

size_t GridGenerator::size_grid()
{
    return _grid.size();
}

size_t GridGenerator::size_elements()
{
    return static_cast<size_t>(_nLoaderPlayer + _nCargo + _nCargoDst + _nBarrier);
}

void GridGenerator::setWidth(int width)
{
    Q_ASSERT(width > 0);
    _width = width;
}

void GridGenerator::setHeight(int height)
{
    Q_ASSERT(height > 0);
    _height = height;
}

void GridGenerator::setLoaderPlayers(int LoaderPlayers)
{
    Q_ASSERT(LoaderPlayers > 0);
    _nLoaderPlayer = LoaderPlayers;
}

void GridGenerator::setCargos(int cargos)
{
    Q_ASSERT(cargos > 0);
    _nCargo = cargos;
}

void GridGenerator::setCargosDestination(int cargosDst)
{
    Q_ASSERT(cargosDst > 0);
    _nCargoDst = cargosDst;
}

void GridGenerator::setBarriers(int barriers)
{
    Q_ASSERT(barriers >= 0);
    _nBarrier = barriers;
}

int GridGenerator::getWidth() const
{
    return _width;
}

int GridGenerator::getHeight() const
{
    return _height;
}

int GridGenerator::getLoaderPlayers() const
{
    return _nLoaderPlayer;
}

int GridGenerator::getCargos() const
{
    return _nCargo;
}

int GridGenerator::getCargosDestination() const
{
    return _nCargoDst;
}

int GridGenerator::getBarriers() const
{
    return _nBarrier;
}

GridType GridGenerator::getGrid() const
{
    return _grid;
}
