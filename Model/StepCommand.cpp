#include <Model/StepCommand.h>

#include <QAbstractItemModel>
#include <QJsonObject>
#include <QJsonArray>

StepCommand::StepCommand(QAbstractItemModel *model, QUndoCommand *parent)
    : QUndoCommand(parent)
    , _pModel(model)
{}

StepCommand::~StepCommand()
{}

bool StepCommand::addArray(const QJsonArray &array)
{
    Q_ASSERT(_pModel);
    foreach(const QJsonValue &jsVal, array)
    {
        QJsonObject jsObj = jsVal.toObject();
        Data data;

        int row = jsObj["row"].toInt();
        int column = jsObj["column"].toInt();
        data.index = _pModel->index(row, column);
        if (!data.index.isValid())
            return false;

        data.newValue = jsObj["newValue"].toInt();
        data.oldValue = jsObj["oldValue"].toInt();
        _dataVec.push_back(data);
    }
    return true;
}

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
    for (int i = _dataVec.size() - 1; i >= 0; --i)
    {
        auto &data = _dataVec[i];
        _pModel->setData(data.index, data.oldValue);
    }
}

QJsonArray StepCommand::array() const
{
    QJsonArray arr;
    foreach(const Data &data, _dataVec)
    {
        QJsonObject jsonData;
        jsonData["row"] = data.index.row();
        jsonData["column"] = data.index.column();
        jsonData["newValue"] = data.newValue.toInt();
        jsonData["oldValue"] = data.oldValue.toInt();
        arr.append(jsonData);
    }
    return arr;
}
