#include "Email/headers/pop3.h"

pop3::pop3(QString server,QString username,QString pwd,Ui::Email *ui)
{
    this->username=username;
    this->pwd=pwd;
    this->server=server;
    this->port=110;
    this->number=1;
    this->socket=new QTcpSocket;
    this->state=NotConnected;
    this->ui=ui;

    connect(socket, SIGNAL( readyRead() ), this, SLOT( readyReadEvent() ) );
    connect(socket, SIGNAL( connected() ), this, SLOT( connectedEvent() ) );
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(errorReceivedEvent(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this,SLOT(stateChangedEvent(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(disconnected()), this,SLOT(disconnectedEvent()));

    socket->blockSignals(false);

    socket->connectToHost(server,port,QIODevice::ReadWrite);

    if(!(socket->waitForConnected(3000))){
       /* QMessageBox msg(this);
        msg.setText("超时");
        msg.exec();*/
    }
}

pop3::~pop3(){}

void pop3::connectedEvent(){
    state=Connected;
}

void pop3::disconnectedEvent(){
    state=NotConnected;
}

void pop3::readyReadEvent(){
    if(state==Connected){
        QString response=socket->readAll();
        response=response.trimmed();
        if(response.contains("+OK")){
            socket->write(QByteArray().append("USER ").append(username).append("\r\n"));
            state=InputUserName;
        }else return;
    }
    if(state==InputUserName){

        QString response=socket->readAll();
        if(response.contains("+OK")){
            socket->write(QByteArray().append("PASS ").append(pwd).append("\r\n"));
            state=InputPassWord;
        }
    }
    if(state==InputPassWord){
        QString response=socket->readAll();
        if(response.contains("+OK")){
            QStringList re=response.split(" ");
            QString nu=re.at(1);
            totalnum=nu.toInt();
            socket->write(QByteArray().append("List").append("\r\n"));
            state=List;
        }
    }
    if(state==List){
        QString response=socket->readAll();
        if(response.contains("+OK")){
            this->sum=response.split(" ").at(1);
            socket->write(QByteArray().append("UIDL").append("\r\n"));
            state=InputUIDL;
        }
    }

    if(state==InputUIDL){
        while(socket->bytesAvailable()>0){
            QString response=socket->readLine();
            emails<<response.trimmed();
            if(response.contains("."))state=WaitDealMail;
        }
        if(state==WaitDealMail){
            emails.removeFirst();
            emails.removeLast();
            while(number<totalnum){
            socket->write(QByteArray().append(tr("RETR %1").arg(number++)).append("\r\n"));//写下载邮件命令，读取邮件内容
            state=ReadContant;
            }
        }
    }

    QStringList MailContent;
    if(state==ReadContant){
        QString response=socket->readAll();
        if(response.contains("Receive")){
            MailContent=response.split("\r\n");
             this->mailcontents=MailContent;
             for(int i=0;i<MailContent.count();i++){
                   // ui->receiveList->addItem(MailContent.at(i));
             }
             qDebug()<<MailContent;
            for(int i=0;i<MailContent.size();i++){
                if(MailContent.at(i).contains("Receive")){
                    this->emails.append(MailContent.at(i));
                    MailContent.begin();
                }

                if(MailContent.at(i).contains("From")){
                    QString send=MailContent.at(i);
                    if(send.contains("<")){
                        send=send.split("<").at(1);
                        if(send.contains(">")){
                            send=send.split(">").at(0);
                            this->fromlist.append(send);
                           // this->tolist.append("15221373597@163.com");
                            this->tolist.append(username);
                            title=send;
                          /*  ui->receiveList->addItem(send);
                            if(color%2==0)
                                ui->receiveList->item(color)->setBackground(QColor::fromRgb(255,169,169,200));
                            else
                                ui->receiveList->item(color)->setBackground(QColor::fromRgb(115,203,219,200));
                            ui->receiveList->item(color)->setForeground(QColor::fromRgb(255,255,255));
                            color++;*/
                        }
                    }
                }

                if(MailContent.at(i).contains("Subject:")){
                    if(MailContent.at(i).contains("Subject:M"))continue;
                    QString sub=MailContent.at(i);
                    QStringList subj=sub.split(" ");
                    sub="";
                    for(int i=1;i<subj.size();i++){
                        sub=sub.append(subj.at(i));
                    }
                    subjectlist.append(sub);
                    title=title.append("                   ").append("Subject: ").append(sub);
                    ui->receiveList->addItem(title);
                    if(color%2==0)
                        ui->receiveList->item(color)->setBackground(QColor::fromRgb(255,169,169,200));
                    else
                        ui->receiveList->item(color)->setBackground(QColor::fromRgb(115,203,219,200));
                    ui->receiveList->item(color)->setForeground(QColor::fromRgb(255,255,255));
                    color++;
                }

                if(MailContent.at(i).contains("Content-Tr")){
                     QString con="";
                    for(int j=i+1;j<MailContent.count();j++){
                        if(MailContent.at(j).contains("Content"))continue;
                        if(MailContent.at(j).contains("---"))continue;
                        if(MailContent.at(j).contains("<div"))continue;
                        con=con.append(MailContent.at(j));
                    }
                    contentlist.append(con);
                    i=MailContent.count();
                }


            }
        }
    }
}

void pop3::stateChangedEvent(QAbstractSocket::SocketState socketState){}

void pop3::errorReceivedEvent(QAbstractSocket::SocketError socketError)
{
    /*QMessageBox msg(this);
    msg.setText("错误："+socketError);
    msg.exec();*/
}
