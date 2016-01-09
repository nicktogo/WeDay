#ifndef TUTOR_H
#define TUTOR_H
#include <QString>

class Tutor
{
public:
    Tutor();
    Tutor(int _id,QString _tel,QString _name);
     Tutor(QString _tel,QString _name);
     QString getTel();
     QString getName();
     int getId();
     void setId(int id);
private:
    int id;
    QString name;
    QString tel;
};

#endif // TUTOR_H
