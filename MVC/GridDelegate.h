#ifndef _GRIDDELEGATE_H_
#define _GRIDDELEGATE_H_

#include <QStyledItemDelegate>

class GridDelegate : public QStyledItemDelegate
{
public:
    GridDelegate(QObject *pParent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QWidget *createEditor(QWidget *pParent, const QStyleOptionViewItem &rcOption, const QModelIndex &rcIndex) const override;
    void setEditorData(QWidget *pEditor, const QModelIndex &rcIndex) const override;
    void setModelData(QWidget *pEditor, QAbstractItemModel *pModel, const QModelIndex &rcIndex) const override;
    void updateEditorGeometry(QWidget *pEditor, const QStyleOptionViewItem &rcOption, const QModelIndex &rcIndex) const override;
};

#endif // !_GRIDDELEGATE_H_
