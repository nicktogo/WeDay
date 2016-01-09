#ifndef NEWTUTOR_H
#define NEWTUTOR_H

#pragma once
#include <QDialog>
#include"table.h"
#include"problem.h"
#include"tutor.h"
#include"email.h"
namespace Ui {
class NewTutor;
}

class NewTutor : public QDialog
{
    Q_OBJECT

public:
    explicit NewTutor(QWidget *parent = 0);
    ~NewTutor();

private slots:




    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();
    void rec_tr(Tutor,QList<Email>*);

    void on_pushButton_4_clicked();

public:
    Tutor searchTr(QString name);

signals:
    void sendtr(Tutor,QList<Email>*);
private:
    Ui::NewTutor *ui;
public:
    Tutor tutor;
    QList<Email>* mail;
};

#endif // NEWTUTOR_H
