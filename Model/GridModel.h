#ifndef _GRIDMODEL_H_
#define _GRIDMODEL_H_

#include <QAbstractTableModel>
#include <QSharedPointer>

#include <FieldFlags.h>
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
    Q_PROPERTY(int step READ step NOTIFY move_changed)
    Q_PROPERTY(int nMoves READ nMoves NOTIFY move_changed)
    Q_PROPERTY(int level READ level NOTIFY grid_changed)
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

    Q_INVOKABLE void next();
    Q_INVOKABLE void previous();

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
    Q_INVOKABLE int step() const;
    Q_INVOKABLE int nMoves() const;
    Q_INVOKABLE int level() const;

signals:
    void data_changed_custom(int row, int col, QVariant data);
    void moved_up();
    void moved_down();
    void moved_left();
    void moved_right();
    void grid_changed();
    void delivered();
    void cargos_left(int nCargos);
    void move_changed();
    void game_win();
private:
    QSharedPointer<GridGenerator> m_pGridGenerator;
    GridType m_beginGrid;
    GridType m_currentGrid;
    QUndoStack *m_pStack;
    QUndoCommand *m_pUndoCmd;
    int m_currStep;
    int m_nSteps;
    int m_nMoves;

    bool moveLoader(int rowOffset, int columnOffset);
    bool move(const QModelIndex &indexBegin, const QModelIndex &indexEnd);
    void movedComplete();
    void addIndexForCommand(const QModelIndex &index, const QVariant &oldValue, const QVariant &newValue);
    void saveStep();
    void createGrid();
    bool checkWin();
    void cmdComplete();

    void setValue(const QModelIndex &index, QVariant value);

    QModelIndex getLoaderPlayerIndex();
    QVariant getValue(const QModelIndex &index) const;
    QVariant getBeginValue(const QModelIndex &index) const;
};

#endif // !_GRIDMODEL_H_
