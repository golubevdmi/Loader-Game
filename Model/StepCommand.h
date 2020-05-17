#ifndef _JSONSTORAGE_H_
#define _JSONSTORAGE_H_

#include <QUndoCommand>
#include <QVariant>
#include <QModelIndex>

class GridModel;

class StepCommand : public QUndoCommand
{
public:
    StepCommand(GridModel *model, QUndoCommand *parent = nullptr);
    ~StepCommand();

    void addIndex(const QModelIndex &index, const QVariant &oldValue, const QVariant &newValue);

    void redo() override;
    void undo() override;

private:
    struct Data
    {
        QModelIndex index;
        QVariant oldValue;
        QVariant newValue;
    };
    GridModel *_pModel;
    QVector<Data> _dataVec;
};

#endif // !_JSONSTORAGE_H_
