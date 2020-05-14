#ifndef _GRIDMODEL_H_
#define _GRIDMODEL_H_

#include <QAbstractTableModel>
#include <QSharedPointer>

#include <GridGenerator/GridGenerator.h>

class GridModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    GridModel(QObject *parent = nullptr);

    Q_INVOKABLE void reset();

    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::EditRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    Q_INVOKABLE void grid5x5();
    Q_INVOKABLE void grid10x10();
    Q_INVOKABLE void grid15x15();

    Q_INVOKABLE int getWidth() const { return _width; }
    Q_INVOKABLE int getHeight() const { return _height; }

signals:
    void grid_changed();
    void loader_index_changed(const QModelIndex &index);
    void cargo_delivered();
    void cargos_left(int nCargos);
    void game_win();
private:
    QSharedPointer<GridGenerator> _gridGenerator;
    GridType _beginGrid;
    GridType _currentGrid;
    int _width;
    int _height;

    void createGrid(int width, int height);
    size_t calcCargosLeft();
};

#endif // !_GRIDMODEL_H_
