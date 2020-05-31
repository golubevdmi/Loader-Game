#ifndef _GRIDMODEL_H_
#define _GRIDMODEL_H_

#include <QAbstractTableModel>
#include <QSharedPointer>

#include <FieldFlags.h>
#include <GridGenerator/GridGenerator.h>

class QUndoStack;
class QUndoCommand;

class SokobanModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(int cargos READ cargos NOTIFY grid_changed)
    Q_PROPERTY(int cargosLeft READ cargosLeft NOTIFY cargos_left)
    Q_PROPERTY(int step READ step NOTIFY move_changed)
    Q_PROPERTY(int nMoves READ nMoves NOTIFY move_changed)
    Q_PROPERTY(int level READ level NOTIFY grid_changed)
    Q_PROPERTY(int nLevels READ nLevels NOTIFY levels_updated)
public:
    SokobanModel(QObject *parent = nullptr);
    ~SokobanModel();

    Q_INVOKABLE void reset();

    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::EditRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE bool loadLevel(int lvlNumber = 0);
    Q_INVOKABLE bool loadNextLvl();
    Q_INVOKABLE bool loadPrevLvl();

    Q_INVOKABLE bool moveUp();
    Q_INVOKABLE bool moveDown();
    Q_INVOKABLE bool moveLeft();
    Q_INVOKABLE bool moveRight();

    Q_INVOKABLE bool undo();
    Q_INVOKABLE bool redo();

    Q_INVOKABLE int cargos() const;
    Q_INVOKABLE int cargosLeft() const;
    Q_INVOKABLE int step() const;
    Q_INVOKABLE int nMoves() const;
    Q_INVOKABLE int level() const;
    Q_INVOKABLE int nLevels() const;

signals:
    void moved_up();
    void moved_down();
    void moved_left();
    void moved_right();
    void move_changed();
    void levels_updated();
    void grid_changed();
    void delivered();
    void cargos_left(int nCargos);
    void game_win();
    void continue_game();
    void quit_game();
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
    bool checkWin() const;
    void cmdComplete();
    void saveStat(int level) const;

    void setValue(const QModelIndex &index, QVariant value);

    QModelIndex getLoaderPlayerIndex();
    QVariant getValue(const QModelIndex &index) const;
    QVariant getBeginValue(const QModelIndex &index) const;

private slots:
    void saveLastGameState() const;
    void loadLastGameState();
};

#endif // !_GRIDMODEL_H_
