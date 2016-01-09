#ifndef EMAILINFO_H
#define EMAILINFO_H

#include <QObject>

class emailInfo : public QObject
{
    Q_OBJECT

private:
    QString address;
    QString username;

public:
    emailInfo();
    emailInfo(const QString & address,const QString & username="");
    ~emailInfo();

    const QString & getAddress() const;
    const QString & getUsername() const;

    void setAddress(const QString & address);
    void setUsername(const QString & username);

};

#endif // EMAILINFO_H
