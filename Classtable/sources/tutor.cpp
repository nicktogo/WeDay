#include "Classtable/headers/tutor.h"

Tutor::Tutor()
{

}
Tutor::Tutor(int _id,QString _tel,QString _name)
{
    this->id=_id;
    this->tel=_tel;
    this->name=_name;

}
Tutor::Tutor(QString _name,QString _tel)
{

    this->tel=_tel;
    this->name=_name;

}
QString Tutor::getTel(){
    return this->tel;
}
int Tutor::getId(){
    return this->id;
}

QString Tutor::getName(){
    return this->name;
}
void Tutor::setId(int id){
    this->id=id;
}
