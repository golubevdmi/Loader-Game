#include <GridWindow.h>

#include <MVC/GridDelegate.h>
#include <MVC/GridModel.h>
#include <MVC/GridTableView.h>

#include <QTableView>
#include <QKeyEvent>
#include <QDebug>

GridWindow::GridWindow(QMainWindow *parent)
    : QMainWindow(parent)
    , _pGridModel(new GridModel(this))
    , _pTableView(new GridTableView(this))
{
    resize(600, 200);
    GridDelegate *pDelegate = new GridDelegate(_pTableView);
    _pTableView->setModel(_pGridModel);
    _pTableView->setItemDelegate(pDelegate);
    setCentralWidget(_pTableView);

    // --TODO Delete later
    connect(_pGridModel, &GridModel::loader_index_changed, [this](const QModelIndex &index) {
        this->_pTableView->setCurrentIndex(index);
    });

    _pGridModel->grid5x5();
}

GridWindow::~GridWindow()
{

}
