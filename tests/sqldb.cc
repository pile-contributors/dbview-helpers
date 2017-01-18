/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file         sqldb.cc
  \date         January 2017
  \author       Nicu Tofan

  \brief        Contains the implementation for SqlDb class.

*//*

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include "sqldb.h"
#include <QStringList>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#define RAND_RNG(Low, High) (qrand() % ((High + 1) - Low) + Low)

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

const char * names[] = {
    "Holli Moskowitz",
    "Fidelia Greenspan",
    "Jamika Davies",
    "Bettyann Walsh",
    "Assunta Ishibashi",
    "Daniele Marzette",
    "Zackary Schneck",
    "Illa Morning",
    "Marshall Bookman",
    "Jamaal Ariola",
    "Wilhelmina Guilliams",
    "Hunter Hutt",
    "Phuong Pasco",
    "Adelina Zeno",
    "Richard Severin",
    "Florene Quisenberry",
    "Virginia Forshee",
    "Wonda Holston",
    "Laverne Severt",
    "Pearline Rux",
    "Jeanmarie Pinzon",
    "Kerrie Hazzard",
    "Benedict Sholes",
    "Dannette Chatfield",
    "Kizzie Batista",
    "Verdell Dimuzio",
    "Tommye Sinn",
    "Eli Deegan",
    "Angelia Elam",
    "Nan Basel",
    "Ardelia Pineiro",
    "Aleisha Gearing",
    "Mui Creager",
    "Allan Mccuin",
    "Gilma Jarboe",
    "Loretta Chaput",
    "Rolanda Looney",
    "Ludivina Jurek",
    "Candra Alverson",
    "Marget Budniewski",
    "Daria Cyrus",
    "Carlo Carnegie",
    "Tatiana Ivester",
    "Gail Grizzle",
    "Vania Loveridge",
    "Kim Farquhar",
    "Jaimee Cambre",
    "Christin Linquist",
    "Johnathan Orenstein",
    "Wilber Ignacio"};

#define names_len (sizeof(names) / sizeof(names[0]))

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
SqlDb::SqlDb (const QString& path) :
    m_db(QSqlDatabase::addDatabase("QSQLITE"))
{
    m_db.setDatabaseName(path);
    // qsrand(qrand());


    if (!m_db.open()) {
       qDebug() << "Error: connection with database fail";
    } else {
       qDebug() << "Database: connection ok";
    }

    if (!m_db.tables().contains (TBL_PERSON)) {
        QSqlQuery query;
        if (!query.exec(
                    "CREATE TABLE " TBL_PERSON " "
                    "  (id INTEGER PRIMARY KEY ASC,"
                    "   name TEXT,"
                    "   age INTEGER);"
                    )) {
            qDebug() << "addPerson error:  "
                     << query.lastError();
        }
    }
    int persc = personsCount();
    if (persc == 0) {
        addRandomPersonToDb (1000-persc);
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
SqlDb::~SqlDb()
{

}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int SqlDb::personsCount()
{
    QSqlQuery query;
    if (!query.exec(
                "SELECT COUNT(id) FROM " TBL_PERSON ";"
                )) {
        qDebug() << "personsCount error:  "
                 << query.lastError();
        return -1;
    } else if (query.next ()) {
        bool b_ok;

        int result = query.value (0).toInt (&b_ok);
        if (!b_ok) {
            qDebug() << "NAN:  " << query.value (0).toString();
            result = -1;
        }
        return result;
    } else {
        qDebug() << "No result (!)";
        return -1;
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void SqlDb::randomPersonData(QString & name, int & age)
{
    int nm = RAND_RNG(0, names_len-1);
    name = names[nm];
    age = RAND_RNG(1, 99);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool SqlDb::addRandomPersonToDb (int count)
{
    bool b_ret = true;
    for (int i = 0; i < count; ++i) {
        QString name;
        int age;
        randomPersonData(name, age);
        if (-1 == addPerson (name, age)) {
            qDebug() << "Failed to insert " << name << " at index " << i;
            b_ret =  false;
            break;
        }
        if (i > 0) {
            if ((i+1) % 100 == 0) {
                qDebug() << "Added " << i+1 << " records";
            }
        }
    }
    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int SqlDb::addPerson (const QString &name, int age)
{
    bool success = false;
    int id = -1;
    // you should check if args are ok first...
    QSqlQuery query;
    query.prepare("INSERT INTO " TBL_PERSON
                  " (name, age) "
                  "VALUES (:name, :age)");
    query.bindValue (":name", name);
    query.bindValue (":age", age);
    if(query.exec()) {
        id = query.lastInsertId().toInt (&success);
    } else {
         qDebug() << "addPerson error:  "
                  << query.lastError();
    }

    return id;
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//

/* ------------------------------------------------------------------------- */
/* ========================================================================= */
