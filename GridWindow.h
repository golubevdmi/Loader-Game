#ifndef _GRIDWINDOW_H_
#define _GRIDWINDOW_H_

#include <QMainWindow>

class GridModel;
class GridTableView;

class GridWindow : public QMainWindow
{
    Q_OBJECT

public:
    GridWindow(QMainWindow *parent = Q_NULLPTR);
    ~GridWindow();

public slots:

private:
    GridModel *_pGridModel;
    GridTableView *_pTableView;
};

#endif // !_GRIDWINDOW_H_
