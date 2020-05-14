#ifndef _GRID_H_
#define _GRID_H_

#include <QVector>

enum FieldValue
{
    Undefined = -1,
    Empty = 0,
    Loader = 1,
    Cargo = 2,
    CargoDestination = 3,
    Barrier = 4
};


using FieldType = int;
using GridType = QVector<FieldType>;


class GridGenerator
{
public:
    GridGenerator();
    virtual ~GridGenerator() {}

    virtual void init();
    virtual void generate();

    size_t size_grid();
    size_t size_elements();

    void setWidth(int width);
    void setHeight(int height);
    void setLoaders(int loaders);
    void setCargos(int cargos);
    void setCargosDestination(int cargosDst);
    void setBarriers(int barriers);

    int getWidth() const;
    int getHeight() const;
    int getLoaders() const;
    int getCargos() const;
    int getCargosDestination() const;
    int getBarriers() const;

    GridType getGrid() const;

protected:
    int _width;
    int _height;
    int _nLoader;
    int _nCargo;
    int _nCargoDst;
    int _nBarrier;
    GridType _grid;

    virtual void fill(FieldType value, int count, GridType &grid) = 0;
};


class RandomGridGenerator : public GridGenerator
{
protected:
    void fill(FieldType value, int count, GridType &grid) override;
};

#endif // !_GRID_H_

