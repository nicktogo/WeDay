
#ifndef NEWTABLE_H
#define NEWTABLE_H
#pragma once
#include <QDialog>
#include"table.h"
#include"problem.h"
#include"tutor.h"
#include"classtableemail.h"
#include<QMap>
#include"assist.h"
namespace Ui {
class NewTable;
}

class NewTable : public QDialog
{
    Q_OBJECT

public:
    explicit NewTable(QWidget *parent = 0);
    ~NewTable();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableWidget_cellClicked(int row, int column);
    void getxy(int,int);
    void ini_table();
    void rec_table(Table,QList<Tutor>*,QList<Problem>*,QList<Email>*);

    void on_pushButton_3_clicked();
    void contextMenuEvent(QContextMenuEvent *event);
    void copy();
    void paste();

signals:
    void  sendxy(int,int,int);
    void  sendt(QString);
    void send_tpe(Table,QList<Tutor>*,QList<Problem>*,QList<Email>*);
public:
    Ui::NewTable *ui;
    QList<Table> *table;
    QList<Assist> *assist;
    QList<Tutor> *tutor;
    QList<Email>*mail;
    QList<Problem>*problem;

    Table *ctable;
    QList<Assist> *cassist;
    QList<Tutor> *ctutor;
    QList<Email>*cmail;
    QList<Problem>*cproblem;
    bool copyok;

    int pos[11][7];
    int i,j;
public:
    int count;
};

#endif // NEWTABLE_H
