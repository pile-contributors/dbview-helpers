#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbview.h"
#include "dbviewmo.h"
#include "dbviewmosi.h"
#include "dbviewmosql.h"
#include "dbviewcolfilter.h"
#include "../dbview_tests.h"
#include "../sqldb.h"

#include <QStandardItemModel>
#include <QStandardItem>
#include <QTimer>
#include <QDateTimeEdit>
#include <QtSql>

static QStandardItemModel * test_model = NULL;

const int row_count = 100;
const int col_count = 10;

#define TEST_DB DBVIEW_BINARY_DIR "/testdb.sqlite"
static SqlDb * sqldb = NULL;

/* ------------------------------------------------------------------------- */
class LocalDbViewMo : public DbViewMo {
public:
    virtual const QAbstractItemModel *
    qtModelC () const {
        return test_model;
    }

    virtual QAbstractItemModel *
    qtModel () {
        return test_model;
    }
};
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
class CustFilter1 : public DbViewColFilter {
public:

    CustFilter1 () :
        DbViewColFilter ()
    {}

    CustFilter1 (const CustFilter1 & other) :
        DbViewColFilter (other)
    {}

    //! The widget to be used for filtering the content of the table.
    virtual QWidget *
    control (
            int column,
            QWidget *parent) {
        return new QDateTimeEdit (parent);
    }

    //! Create an exact duplicate of this one.
    virtual DbViewColFilter *
    clone() const {
        return new CustFilter1 (*this);
    }

    //! Tell if this filter accepts provided piece of data.
    virtual bool
    acceptsData (
            const QVariant & data) const {
        return true;
    }
};
/* ========================================================================= */

static LocalDbViewMo * local_model = new LocalDbViewMo();
static DbViewMoSi * simple_model = new DbViewMoSi();
static DbViewMoSql * sql_model = NULL;

/* ------------------------------------------------------------------------- */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer::singleShot (1000, this, &MainWindow::delayedInit);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
MainWindow::~MainWindow()
{
    delete ui;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void MainWindow::delayedInit ()
{
    if (test_model == NULL) {
        initModel ();
    }

    ui->widget->setUserModel (simple_model);
    // ui->widget->setUserModel (local_model);
    ui->widget->setColumnFilter (0, true, QString("R10*"));
    ui->widget->setColumnFilter (1, true, QStringList() << "1" << "2");
    ui->widget->setColumnFilterChoice (1, true, QStringList() << "1" << "2");



    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "mycn");
    db.setDatabaseName(TEST_DB);
    Q_ASSERT(db.open());
    sql_model = new DbViewMoSql(db, TBL_PERSON, this);

    ui->widget_2->setUserModel (sql_model);
    ui->widget_2->setColumnFilter (1, true, QString(""));

}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void MainWindow::initModel ()
{
    sqldb = new SqlDb(TEST_DB);


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

    simple_model->setSourceModel (test_model);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
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
/* ========================================================================= */

