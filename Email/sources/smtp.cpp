#include "Email/headers/smtp.h"

#include <QFileInfo>
#include <QByteArray>

SMTP::SMTP(const QString & host, int port, ConnectionType type)
    :name("localhost"),authmethod(AuthPlain),
      connectionTimeout(5000),responseTimeout(5000)
{
    setConnectionType(type);
    this->host=host;
    this->port=port;

    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(socketStateChanged(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(socketError(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(readyRead()),
            this, SLOT(socketReadyRead()));

}

SMTP::~SMTP(){}



void SMTP::setUsername(const QString &host)
{
    this->username = host;
}
const QString& SMTP::getUsername() const
{
    return this->username;
}

void SMTP::setPwd(const QString &password)
{
    this->pwd = password;
}
const QString& SMTP::getPwd() const
{
    return this->pwd;
}

void SMTP::setAuthMethod(AuthMethod method)
{
    this->authmethod = method;
}
SMTP::AuthMethod SMTP::getAuthMethod() const
{
    return this->authmethod;
}

void SMTP::setHost(QString &host)
{
    this->host = host;
}
const QString& SMTP::getHost() const
{
    return this->host;
}

void SMTP::setPort(int port)
{
    this->port = port;
}
int SMTP::getPort() const
{
    return this->port;
}

void SMTP::setConnectionType(ConnectionType type)
{
    this->type = type;

    switch (type)
    {
    case TcpConnection:
        socket = new QTcpSocket(this);
        break;
    case SslConnection:
    case TlsConnection:
        socket = new QSslSocket(this);
    }
}
SMTP::ConnectionType SMTP::getConnectionType() const
{
    return type;
}

void SMTP::setName(const QString &name)
{
    this->name = name;
}
const QString& SMTP::getName() const
{
    return this->name;
}

void SMTP::setConnectionTimeout(int time)
{
    connectionTimeout = time;
}
int SMTP::getConnectionTimeout() const
{
    return connectionTimeout;
}

void SMTP::setResponseTimeout(int time)
{
    responseTimeout = time;
}
int SMTP::getResponseTimeout() const
{
    return responseTimeout;
}

const QString & SMTP::getResponseText() const
{
    return responseText;
}

int SMTP::getResponseCode() const
{
    return responseCode;
}

QTcpSocket* SMTP::getSocket() {
    return socket;
}


bool SMTP::connectHost(){
    switch(type){
    case TlsConnection:
    case TcpConnection:
        socket->connectToHost(host,port);
        break;
    case SslConnection:
        ((QSslSocket*)socket)->connectToHostEncrypted(host,port);
        break;
    }

    //Connect time out
    if(!socket->waitForConnected(connectionTimeout)){
        emit smtpError(ConnectionTimeoutError);
        return false;
    }

    try{
        waitForResponse();

        if(responseCode!=220){
            emit smtpError(ServerError);
            return false;
        }

        sendMessage("EHLO "+name);

        waitForResponse();

        if(responseCode!=250){
            emit smtpError(ServerError);
            return false;
        }

        if(type==TlsConnection){
            sendMessage("STARTTLS");
            waitForResponse();
            if(responseCode!=220){
                emit smtpError(ServerError);
                return false;
            };
            ((QSslSocket*) socket)->startClientEncryption();

            if (!((QSslSocket*) socket)->waitForEncrypted(connectionTimeout)) {
                qDebug() << ((QSslSocket*) socket)->errorString();
                emit SmtpError(ConnectionTimeoutError);
                return false;
            }

            sendMessage("EHLO " + name);
            waitForResponse();
            if (responseCode != 250) {
                emit smtpError(ServerError);
                return false;
            }
        }
    } catch (ResponseTimeoutException)
    {
        return false;
    }
    return true;
}



bool SMTP::login(){
    return login(username,pwd,authmethod);
}

bool SMTP::login(const QString &username,const QString &pwd,AuthMethod method){

    try{
        if(method==AuthPlain){
            sendMessage("AUTH PLAIN"+QByteArray().append((char)0).append(username).append((char)0).append(pwd).toBase64());
            waitForResponse();
            if(responseCode!=235){
                emit smtpError(AuthenticationFailedError);
                return false;
            }
        }
        else if(method==AuthLogin){
            sendMessage("AUTH LOGIN");
            waitForResponse();
            if(responseCode!=334){
                emit smtpError(AuthenticationFailedError);
                return false;
            }
            sendMessage(QByteArray().append(username).toBase64());

            waitForResponse();
            if(responseCode!=334){
                emit smtpError(AuthenticationFailedError);
                return false;
            }

            sendMessage(QByteArray().append(pwd).toBase64());
            waitForResponse();
            if(responseCode!=235){
                emit smtpError(AuthenticationFailedError);
                return false;
            }
        }
    }catch(ResponseTimeoutException e){
        emit smtpError(AuthenticationFailedError);
        return false;
    }
    return true;
}


bool SMTP::sendMail(Message &email){
    try{
        sendMessage("MAIL FROM: <"+email.getSender().getAddress()+">");
        waitForResponse();
        if(responseCode!=250)return false;

        QList<emailInfo*>::const_iterator itBegin,itEnd;

        for(itBegin=email.getReceivers().begin(),itEnd=email.getReceivers().end();
            itBegin!=itEnd;++itBegin){
            sendMessage("RCPT TO: <"+(*itBegin)->getAddress()+">");
            waitForResponse();
            if(responseCode!=250)return false;
        }

        for(itBegin=email.getReceivers(Message::Cc).begin(),itEnd=email.getReceivers(Message::Cc).end();
            itBegin!=itEnd;++itBegin){
            sendMessage("RCPT TO: <"+(*itBegin)->getAddress()+">");
            waitForResponse();
            if(responseCode!=250)return false;
        }

        for(itBegin=email.getReceivers(Message::Bcc).begin(),itEnd=email.getReceivers(Message::Bcc).end();
            itBegin!=itEnd;++itBegin){
            sendMessage("RCPT TO: <"+(*itBegin)->getAddress()+">");
            waitForResponse();
            if(responseCode!=250)return false;
        }

        sendMessage("DATA");
        waitForResponse();
        if(responseCode!=354)return false;

        sendMessage(email.toString());

        sendMessage(".");

        waitForResponse();
        if(responseCode!=250&&responseCode!=554)
            return false;
    }catch(ResponseTimeoutException){
        return false;
    }
    return true;
}


void SMTP::waitForResponse()throw (ResponseTimeoutException){
    do{
        if(!socket->waitForReadyRead(responseTimeout)){
            emit smtpError(ResponseTimeoutError);
            throw ResponseTimeoutException();
        }

        while(socket->canReadLine()){
            responseText=socket->readLine();

            responseCode=responseText.left(3).toInt();

            if(responseCode/100==4)
                emit smtpError(ServerError);
            if(responseCode/100==5)
                emit smtpError(ClientError);
            if(responseText[3]==' '){return;}
        }
    }while(true);
}

void SMTP::sendMessage(const QString &text){
    socket->write(text.toUtf8()+"\r\n");
}

void SMTP::quit(){
    sendMessage("QUIT");
}

void SMTP::socketStateChanged(QAbstractSocket::SocketState state){}

void SMTP::socketError(QAbstractSocket::SocketError socketError){}

void SMTP::socketReadyRead(){}
