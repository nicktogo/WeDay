#ifndef NEWCLASS_H
#define NEWCLASS_H

#pragma once
#include <QDialog>
#include"table.h"
#include"problem.h"
#include"tutor.h"
#include"classtableemail.h"

namespace Ui {
class NewClass;
}

class NewClass : public QDialog
{
    Q_OBJECT

public:
    explicit NewClass(QWidget *parent = 0);

    ~NewClass();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();
    void receivexy(int,int,int);
    void on_pushButton_clicked();
    void rec_tr(Tutor tr,QList<Email>*le);
    void rec_pr(QList<Problem>*lp);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_comboBox_6_currentTextChanged(const QString &arg1);

    void on_pushButton_3_clicked();

    void on_comboBox_6_currentIndexChanged(const QString &arg1);

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();
    void rec_type(int,int,int,QString);
    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();
    void rec_tpe(Table,QList<Tutor>*,QList<Problem>*,QList<Email>*);



signals:
    void  sendtable(Table,QList<Tutor>*,QList<Problem>*,QList<Email>*);
    void  sendmail(QList<Email>*);
    void sendtr(Tutor,QList<Email>*);
    void sendp(QList<Email>*,Problem*);
private:
    Ui::NewClass *ui;
public:

    QMap<int,int> *assist;
    QList<Tutor> *tutor;
    QList<Email>*mail;
    QList<Problem>*problem;
    QList<Problem> *dp;
    QList<int> *dt;
    QString tname;
    QMap<QString,int>* pn;

    int i,j,count,sendtype;
};

#endif // NEWCLASS_H
