#ifndef _GRIDTABLEVIEW_H_
#define _GRIDTABLEVIEW_H_

#include <QTableView>

class GridTableView : public QTableView
{
    Q_OBJECT
public:
    GridTableView(QWidget *parent = nullptr);
    ~GridTableView();

    //void setCurrentIndex(const QModelIndex &index) override;

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    bool moveCell(const QModelIndex &indexBegin, const QModelIndex &indexEnd);

private slots:
    // --TODO
    void setLoaderAsCurrentIndex();
};

#endif // !_GRIDTABLEVIEW_H_
