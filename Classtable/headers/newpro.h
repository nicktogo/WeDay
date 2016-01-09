#ifndef NEWPRO_H
#define NEWPRO_H

#pragma once
#include <QDialog>
#include"email.h"
#include"table.h"
#include"problem.h"
#include"tutor.h"
#include<QStandardItemModel>
namespace Ui {
class NewPro;
}

class NewPro : public QDialog
{
    Q_OBJECT

public:
    explicit NewPro(QWidget *parent = 0);
    ~NewPro();
signals:
    void sendpr(QList<Problem>*);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void itemClicked(QModelIndex index);
    void getData();

    void rec_mail(QList<Email>*);
    void rec_p(QList<Email>*,Problem*);

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::NewPro *ui;
    QList<Problem>* problem;
    QStandardItemModel *standardItemModel;
    QList<Email> *mail;
};

#endif // NEWPRO_H
