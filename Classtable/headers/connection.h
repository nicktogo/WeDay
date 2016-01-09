#ifndef CONNECTION
#define CONNECTION
#define CONNECTION_H
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
   // db.setDatabaseName(":memory:");
    db.setDatabaseName("t.db");
    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection."
                     ), QMessageBox::Cancel);
        return false;
    }

    QSqlQuery query;
        query.exec("create table subject (id int,name string,teacher string,week int,ttime int,tname string,classroom string,type string)");
        query.exec("create table tutor (id int,name string,tel string)");
        query.exec("create table mail (id int,mail string)");
        query.exec("create table assist (class_id int,tutor_id int)");
        query.exec("create table problem (class_id int,title string,type int,text string,ttime string,mail string)");
        query.exec("insert into subject (id,name,teacher,week,time,tname,classroom,type) values(0,'math','aaa',0,0,'t1','a111','both')");


    return true;
}

#endif // CONNECTION

