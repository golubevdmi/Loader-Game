#include <MVC/GridTableView.h>

#include <GridGenerator/GridGenerator.h>

#include <QKeyEvent>
#include <QModelIndex>
#include <QDebug>

GridTableView::GridTableView(QWidget *parent)
    : QTableView(parent)
{
    // --TODO
    connect(model(), &QAbstractTableModel::modelReset, this, &GridTableView::setLoaderAsCurrentIndex);
}

GridTableView::~GridTableView()
{}

void GridTableView::keyPressEvent(QKeyEvent *event)
{
    QModelIndex indexBegin = currentIndex();
    QModelIndex indexEnd;

    if (indexBegin.isValid())
    {
        switch (event->key())
        {
        case Qt::Key_Left:
            indexEnd = model()->index(indexBegin.row(), indexBegin.column() - 1);
            break;
        case Qt::Key_Right:
            indexEnd = model()->index(indexBegin.row(), indexBegin.column() + 1);
            break;
        case Qt::Key_Up:
            indexEnd = model()->index(indexBegin.row() - 1, indexBegin.column());
            break;
        case Qt::Key_Down:
            indexEnd = model()->index(indexBegin.row() + 1, indexBegin.column());
            break;
        }
    }

    if (moveCell(indexBegin, indexEnd))
    {
        QTableView::keyPressEvent(event);
    }
    qDebug() << static_cast<Qt::Key>(event->key());
}

bool GridTableView::moveCell(const QModelIndex &indexBegin, const QModelIndex &indexEnd)
{
    if (!indexBegin.isValid() || !indexEnd.isValid())
        return false;

    switch (indexEnd.data().toInt())
    {
    case FieldValue::Cargo:
    {
        switch (indexBegin.data().toInt())
        {
        case FieldValue::Loader:
        {
            int row = indexEnd.row() + indexEnd.row() - indexBegin.row();
            int column = indexEnd.column() + indexEnd.column() - indexBegin.column();
            QModelIndex indexEnd2 = model()->index(row, column);
            if (moveCell(indexEnd, indexEnd2))
            {
                QVariant beginData = indexBegin.data();
                bool ret = false;
                ret |= model()->setData(indexBegin, static_cast<QVariant>(FieldValue::Empty));
                ret |= model()->setData(indexEnd, beginData.toInt());
                return ret;
            }
        }
        }
        return false;
    }
    case FieldValue::Barrier:
        return false;
    default:
    {
        QVariant beginData = indexBegin.data();
        bool ret = false;
        ret |= model()->setData(indexBegin, static_cast<QVariant>(FieldValue::Empty));
        ret |= model()->setData(indexEnd, beginData.toInt());
        return ret;
    }
    }
}

// --TODO
void GridTableView::setLoaderAsCurrentIndex()
{
    QModelIndexList matches = model()->match(model()->index(0, 0),
                                             Qt::ItemDataRole::EditRole,
                                             static_cast<QVariant>(FieldValue::Loader));

    qDebug() << "find";
    foreach(const QModelIndex &index, matches)
    {
        setCurrentIndex(index);
        qDebug() << index;
    }
}
