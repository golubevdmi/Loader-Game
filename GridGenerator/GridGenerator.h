#ifndef _GRID_H_
#define _GRID_H_

#include <QVector>

enum FieldValue
{
    Undefined = Qt::UserRole,
    Empty,
    LoaderPlayer,
    Cargo,
    CargoDestination,
    Barrier
};

using GridType = QVector<int>;


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
    void setLoaderPlayers(int LoaderPlayers);
    void setCargos(int cargos);
    void setCargosDestination(int cargosDst);
    void setBarriers(int barriers);

    int getWidth() const;
    int getHeight() const;
    int getLoaderPlayers() const;
    int getCargos() const;
    int getCargosDestination() const;
    int getBarriers() const;

    GridType getGrid() const;

protected:
    int _width;
    int _height;
    int _nLoaderPlayer;
    int _nCargo;
    int _nCargoDst;
    int _nBarrier;
    GridType _grid;

    virtual void fill(int value, int count, GridType &grid) = 0;
};


class RandomGridGenerator : public GridGenerator
{
protected:
    void fill(int value, int count, GridType &grid) override;
};

#endif // !_GRID_H_

