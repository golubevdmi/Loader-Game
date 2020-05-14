#include <MVC/GridDelegate.h>
#include <MVC/GridModel.h>

#include <QLineEdit>
#include <QPainter>


GridDelegate::GridDelegate(QObject *pParent)
    : QStyledItemDelegate(pParent)
{}

void GridDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    switch (index.model()->data(index, Qt::DisplayRole).toInt())
    {
    case FieldValue::Loader:
        painter->fillRect(option.rect, QBrush(Qt::green));
        break;
    case FieldValue::Cargo:
        painter->fillRect(option.rect, QBrush(Qt::blue));
        break;
    case FieldValue::CargoDestination:
        painter->fillRect(option.rect, QBrush(Qt::gray));
        break;
    case FieldValue::Barrier:
        painter->fillRect(option.rect, QBrush(Qt::black));
        break;
    default:
        painter->fillRect(option.rect, QBrush(Qt::white));
        break;
    }
}

QWidget *GridDelegate::createEditor(QWidget *pParent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QLineEdit *pEdit = new QLineEdit(pParent);
    return pEdit;
}

void GridDelegate::setEditorData(QWidget *pEditor, const QModelIndex &rcIndex) const
{
    const int cnValue = rcIndex.model()->data(rcIndex, Qt::EditRole).toInt();
    QLineEdit *pEdit = qobject_cast <QLineEdit *> (pEditor);
    if (pEdit)
        pEdit->setText(QString::number(cnValue));
}

void GridDelegate::setModelData(QWidget *pEditor, QAbstractItemModel *pModel, const QModelIndex &rcIndex) const
{
    QLineEdit *pEdit = qobject_cast <QLineEdit *> (pEditor);
    if (pEdit)
    {
        const int cnValue = pEdit->text().toInt();
        pModel->setData(rcIndex, cnValue, Qt::EditRole);
    }
}
void GridDelegate::updateEditorGeometry(QWidget *pEditor, const QStyleOptionViewItem &rcOption, const QModelIndex &index) const
{
    Q_UNUSED(index);
    pEditor->setGeometry(rcOption.rect);
}
