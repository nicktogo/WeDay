#ifndef POP3_H
#define POP3_H

#include <QObject>
#include <QtCore>
#include <QtNetwork/QTcpSocket>
#include <QMessageBox>
#include "ui_email.h"

class pop3:public QObject
{
    Q_OBJECT

private:

    QString pwd;

    QTcpSocket *socket;
    QString server;
    int port;


    int number;
    QString sum;

    int state;
    int totalnum;
    int color=0;
    QString title="";



    enum ConnectionState{
        NotConnected,
        Connected,
        InputUserName,
        InputPassWord,
        List,
        InputUIDL,
        WaitDealMail,
        ReadMailList,
        ReadContant,
        ReadContantOver,
        DELMail,
        DELMailOver
    };

public slots:
    void stateChangedEvent(QAbstractSocket::SocketState socketState);
    void errorReceivedEvent(QAbstractSocket::SocketError socketError);
    void disconnectedEvent();
    void connectedEvent();
    void readyReadEvent();
public:
    pop3(QString server,QString username,QString pwd,Ui::Email *ui);
    ~pop3();
     QStringList emails;
     QStringList mailcontents;
     QStringList fromlist;
     QStringList tolist;
     QStringList subjectlist;
     QStringList contentlist;
     QStringList attchlist;
     Ui::Email *ui;
     QString username;
};

#endif // POP3_H
