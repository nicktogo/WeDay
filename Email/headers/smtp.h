#ifndef SMTP_H
#define SMTP_H

#include <QObject>
#include <QtNetwork/QSslSocket>

#include "message.h"

class SMTP:public QObject
{
    Q_OBJECT
public:

    enum ConnectionType{
        TcpConnection,
        SslConnection,
        TlsConnection
    };

    enum AuthMethod{
        AuthPlain,
        AuthLogin
    };

    enum SmtpError{
        ConnectionTimeoutError,
        ResponseTimeoutError,
        AuthenticationFailedError,
        ServerError,
        ClientError
    };

    SMTP(const QString & host="localhost",int port=25,ConnectionType type=TcpConnection);
    ~SMTP();

    void setHost(QString &host);
    const QString& getHost()const;

    void setPort(int port);
    int getPort()const;

    void setName(const QString &name);
    const QString & getName() const;

    void setConnectionType(ConnectionType type);
    ConnectionType getConnectionType() const;

    void setUsername(const QString &host);
    const QString & getUsername() const;

    void setPwd(const QString &password);
    const QString & getPwd() const;

    void setAuthMethod(AuthMethod method);
    SMTP::AuthMethod getAuthMethod() const;

    void setConnectionTimeout(int time);
    int getConnectionTimeout() const;

    void setResponseTimeout(int time);
    int getResponseTimeout() const;

    const QString & getResponseText() const;
    int getResponseCode() const;

    QTcpSocket* getSocket();

    bool connectHost();
    bool login();
    bool login(const QString &username,const QString &pwd,AuthMethod method=AuthLogin);
    bool sendMail(Message&email);
    void quit();

protected:

    QTcpSocket *socket;

    QString name;
    QString host;
    int port;
    ConnectionType type;

    QString username;
    QString pwd;
    AuthMethod authmethod;

    int connectionTimeout;
    int responseTimeout;

    QString responseText;
    int responseCode;

    class ResponseTimeoutException{};

    void waitForResponse()throw(ResponseTimeoutException);

    void sendMessage(const QString &text);



protected slots:

    void socketStateChanged(QAbstractSocket::SocketState state);
    void socketError(QAbstractSocket::SocketError error);
    void socketReadyRead();

signals:
    void smtpError(SmtpError se);

};

#endif // SMTP_H
