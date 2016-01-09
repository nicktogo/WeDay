#pragma once
#include "QString"



class Table
{
private :
    int id;
    QString classname;
    QString classroom;
    QString teacher;
    int week;
    int ttime;
    QString tname;
    QString type;

public:
    Table();
    Table(int _id,QString _name,QString _teacher,int _week,int _time,QString _tname);
    Table(QString _name,QString _teacher,int _week,int _time,QString classroom,QString type);
public:
    void setClassname(QString name);
    void setClassroom(QString name);
    void setTeacher(QString name);
    void setWeek(int ttime);
    void setTime(int ttime);
    void setTname(QString name);
    void setType(QString type);
    void setId(int);
    int getId();
    QString getClassname();
    QString getClassroom();
    QString getTeacher();
    int getWeek();
    int getTime();
    QString getTname();
    QString getType();

};


