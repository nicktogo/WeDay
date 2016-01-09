#ifndef PROBLEM_H
#define PROBLEM_H
#include <QString>

class Problem
{
public:
    Problem();

    Problem(int _id,QString _title,int _type,QString _text,QString _ddl,QString _mail);
Problem(QString _title,int _type,QString _text,QString _ddl,QString _mail);
QString getTitle();
int getType();
QString getTexe();
QString getDdl();
QString getMail();
void setId(int);
int getId();
void  copy(Problem p);

public:
    int id;
    QString title;
    QString text;
    int type;
    QString ddl;
    QString mail;

};

#endif // PROBLEM_H
