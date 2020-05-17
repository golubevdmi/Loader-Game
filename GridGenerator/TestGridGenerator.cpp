#include <GridGenerator/GridGenerator.h>

void TestGridGenerator::generate()
{
    if (_width != _height)
        return;
    int sz = _width;
    switch (sz)
    {
    case 5:
        grid5x5();
        break;
    case 10:
        grid10x10();
        break;
    case 15:
        grid15x15();
        break;
    }
}

void TestGridGenerator::fill(int value, int count, GridType &grid)
{}

void TestGridGenerator::grid5x5()
{
    int center = _width / 2;
    int border = _width - 1;

    _grid[center * _height + center] = LoaderPlayer;

    _grid[(center - 1) * _height + center - 1] = Cargo;
    _grid[(center + 1) * _height + center + 1] = Cargo;

    _grid[(center - 1) * _height + center + 1] = CargoDestination;
    _grid[(center + 1) * _height + center - 1] = CargoDestination;

    _grid[border * _height + border] = Barrier;
    _grid[border * _height + 0] = Barrier;
    _grid[0 * _height + border] = Barrier;
    _grid[0 * _height + 0] = Barrier;
}

void TestGridGenerator::grid10x10()
{
    int center = _width / 2;
    int border = _width - 1;

    _grid[center * _height + center] = LoaderPlayer;

    _grid[(center - 1) * _height + center - 1] = Cargo;
    _grid[(center + 1) * _height + center + 1] = Cargo;

    _grid[(center - 1) * _height + center + 1] = CargoDestination;
    _grid[(center + 1) * _height + center - 1] = CargoDestination;

    _grid[border * _height + border] = Barrier;
    _grid[border * _height + 0] = Barrier;
    _grid[0 * _height + border] = Barrier;
    _grid[0 * _height + 0] = Barrier;
}

void TestGridGenerator::grid15x15()
{
    int center = _width / 2;
    int border = _width - 1;

    _grid[center * _height + center] = LoaderPlayer;

    _grid[(center - 1) * _height + center - 1] = Cargo;
    _grid[(center + 1) * _height + center + 1] = Cargo;

    _grid[(center - 1) * _height + center + 1] = CargoDestination;
    _grid[(center + 1) * _height + center - 1] = CargoDestination;

    _grid[border * _height + border] = Barrier;
    _grid[border * _height + 0] = Barrier;
    _grid[0 * _height + border] = Barrier;
    _grid[0 * _height + 0] = Barrier;
}
