#ifndef EMAIL_H
#define EMAIL_H
#include <QString>

class Email
{
public:
    Email();
    Email(int,QString);
    Email(QString);
    QString getAdd();
    void copy(Email);
    void setId(int id);
int getId();
private:
    int tutor_id;
    QString add;
};

#endif // EMAIL_H
