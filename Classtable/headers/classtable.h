#ifndef CLASSTABLE_H
#define CLASSTABLE_H

#pragma once
#include <QMainWindow>
#include <QMouseEvent>
#include <QList>
#include"newtable.h"
#include"classtableemail.h"
#include <QDialog>
#include"table.h"
#include"problem.h"
#include"tutor.h"
#include <QSqlQuery>
namespace Ui {
class Classtable;
}

class Classtable : public QMainWindow
{
    Q_OBJECT

public:
    explicit Classtable(QWidget *parent = 0);
    ~Classtable();

private slots:


    void on_tableWidget_cellClicked(int row, int column);

    void getxy(int,int);


    void on_pushButton_clicked();
void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();
    void rec_table(QString);
signals:
    void send_type(int,int,int,QString);
private:

    void ini_table();
    void ini_combx();
    void cleartable();

private:
    Ui::Classtable *ui;
public:
    QList<Table> *table;
    QMap<int,int> *assist;
    QList<Tutor> *tutor;
    QList<Email>*mail;
    QList<Problem>*problem;
    int pos[11][7];
    int i,j;

};

#endif // MAINWINDOW_H

