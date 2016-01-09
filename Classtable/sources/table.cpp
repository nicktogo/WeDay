#include "Classtable/headers/table.h"

Table::Table()
{



}


Table::Table(int _id,QString _name,QString _teacher,int _week,int _time,QString _tname){
    this->id=_id;
    this->classname=_name;
    this->teacher=_teacher;
    this->ttime=_time;
    this->week=_week;
    this->tname=_tname;

}


Table::Table(QString _name,QString _teacher,int _week,int _time,QString classroom,QString type){

    this->classname=_name;
    this->teacher=_teacher;
    this->ttime=_time;
    this->week=_week;
    this->classroom=classroom;
    this->type=type;


}
void Table::setClassname(QString name){
    this->classname=name;
}
void Table::setClassroom(QString name){
    this->classroom=name;
}
void Table::setType(QString name){
    this->type=name;
}

void Table::setTeacher(QString name){
    this->teacher=name;
}

void Table::setWeek(int ttime){
    this->week=ttime;
}

void Table::setTime(int ttime){
    this->ttime=ttime;
}

void Table::setTname(QString name){
    this->tname=name;
}

QString Table::getClassname(){
    return this->classname;
}
QString Table::getClassroom(){
    return this->classroom;
}
QString Table::getTeacher(){
    return this->teacher;
}

int Table::getWeek(){
    return this->week;
}
int Table::getTime(){
    return this->ttime;
}

QString Table::getTname(){
    return this->tname;
}
QString Table::getType(){
    return this->type;
}
void Table::setId(int id){
    this->id=id;
}
int Table::getId(){
    return this->id;
}
