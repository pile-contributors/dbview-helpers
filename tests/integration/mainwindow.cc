#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbview.h"

#include <QStandardItemModel>
#include <QStandardItem>

static QStandardItemModel * test_model = NULL;

const int row_count = 10;
const int col_count = 10;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (test_model == NULL) {
        initModel ();
    }

    ui->widget->setModel (test_model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initModel ()
{
    test_model = new QStandardItemModel();
    int i, j;

    bool first = true;
    test_model->setRowCount (row_count);
    for (i=0; i<row_count; ++i) {
        for (j=0; j<col_count; ++j) {
            if (first) {
                test_model->setHorizontalHeaderItem (
                            j, new QStandardItem(QString("Column %1").arg(j)));
            }
            QStandardItem * item = new QStandardItem(QString("R%1 C%2").arg(i).arg(j));
            test_model->setItem(i, j, item);
        }
        first = false;
        test_model->setVerticalHeaderItem(
                    i, new QStandardItem(QString("Row %1").arg(i)));
    }
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
