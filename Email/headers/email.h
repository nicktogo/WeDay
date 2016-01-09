#ifndef EMAIL_H
#define EMAIL_H

#include <QWidget>
#include "mimesmtp.h"
#include "qlistwidget.h"

namespace Ui {
class Email;
}

class Email: public QWidget
{
    Q_OBJECT
public:
    explicit Email(QWidget *parent = 0,QString nickName=" ",QString email=" ",QString pwd=" ");
    void setEmail(QString & email);
    const QString getEmail()const;

    void setNickName(QString & nickName);
    const QString getNickName()const;

    static emailInfo * stringToEmail(const QString &string);

    QString charToString(char * ch);
    char * stringToChar(QString str);

    pop3 *pop;
    QStringList drafts;
    QStringList drsender;
    QStringList drreceiver;
    QStringList drsubject;
    QStringList drattachment;
    QStringList drcontents;

signals:

public slots:
    void on_inboxBT_clicked();
    void on_outboxBT_clicked();
    void on_addBT_clicked();
    void on_cleanBT_clicked();
    void on_sendBT_clicked();
    void on_saveBT_clicked();
    void on_draftBT_clicked();
    void on_draftList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_receiveList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
private:
    Ui::Email *ui;
    QString email;
    QString nickName;
    QString pwd;
};

#endif // EMAIL_H
