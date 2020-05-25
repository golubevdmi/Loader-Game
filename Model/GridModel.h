#ifndef _GRIDMODEL_H_
#define _GRIDMODEL_H_

#include <QAbstractTableModel>
#include <QSharedPointer>

#include <GridGenerator/GridGenerator.h>

class QUndoStack;
class QUndoCommand;

class GridModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(int cargos READ cargos NOTIFY grid_changed)
    Q_PROPERTY(int cargosDst READ cargosDst NOTIFY grid_changed)
    Q_PROPERTY(int barriers READ barriers NOTIFY grid_changed)
    Q_PROPERTY(int cargosLeft READ cargosLeft NOTIFY cargos_left)
public:
    GridModel(QObject *parent = nullptr);
    ~GridModel();

    Q_INVOKABLE void reset();

    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::EditRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void grid5x5();
    Q_INVOKABLE void grid10x10();
    Q_INVOKABLE void grid15x15();

    Q_INVOKABLE bool moveUp();
    Q_INVOKABLE bool moveDown();
    Q_INVOKABLE bool moveLeft();
    Q_INVOKABLE bool moveRight();

    Q_INVOKABLE bool undo();
    Q_INVOKABLE bool redo();

    Q_INVOKABLE int cargos() const;
    Q_INVOKABLE int cargosDst() const;
    Q_INVOKABLE int barriers() const;
    Q_INVOKABLE int cargosLeft() const;

signals:
    void grid_changed();
    void loader_index_changed(const QModelIndex &index);
    void cargo_delivered();
    void cargos_left(int nCargos);
    void game_win();
private:
    QSharedPointer<GridGenerator> m_pGridGenerator;
    GridType m_beginGrid;
    GridType m_currentGrid;
    QUndoStack *m_pStack;
    QUndoCommand *m_pUndoCmd;
    int m_width;
    int m_height;
    int m_nSteps;
    int m_nMoves;

    bool moveLoader(int rowOffset, int columnOffset);
    bool move(const QModelIndex &indexBegin, const QModelIndex &indexEnd);
    void movedComplete();
    void addIndexForCommand(const QModelIndex &index, const QVariant &oldValue, const QVariant &newValue);
    void saveStep();
    void createGrid(int width, int height);
    bool checkWin();
    void cmdComplete();

    void setValue(const QModelIndex &index, QVariant value);

    QModelIndex getLoaderPlayerIndex();
    QVariant getValue(const QModelIndex &index) const;
    QVariant getBeginValue(const QModelIndex &index) const;
};

#endif // !_GRIDMODEL_H_
