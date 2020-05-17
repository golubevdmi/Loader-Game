#include <Model/StepCommand.h>

#include <Model/GridModel.h>

StepCommand::StepCommand(GridModel *model, QUndoCommand *parent)
    : QUndoCommand(parent)
    , _pModel(model)
{}

StepCommand::~StepCommand()
{}

void StepCommand::addIndex(const QModelIndex &index, const QVariant &oldValue, const QVariant &newValue)
{
    Data data;
    data.index = index;
    data.oldValue = oldValue;
    data.newValue = newValue;
    _dataVec.push_back(data);
}

void StepCommand::redo()
{
    Q_ASSERT(_pModel);
    foreach (const Data &data, _dataVec)
    {
        _pModel->setData(data.index, data.newValue);
    }
}

void StepCommand::undo()
{
    Q_ASSERT(_pModel);
    foreach (const Data &data, _dataVec)
    {
        _pModel->setData(data.index, data.oldValue);
    }
}
