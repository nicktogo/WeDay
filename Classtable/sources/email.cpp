#include "Classtable/headers/email.h"
#include<QString>
Email::Email()
{

}
Email::Email(int _id,QString _add)
{
    this->tutor_id=_id;
    this->add=_add;

}

Email::Email(QString _add)
{

    this->add=_add;

}
 QString Email::getAdd(){return this->add;}
void Email::copy(Email e){

    this->tutor_id=e.tutor_id;
    this->add=e.add;
}
void Email::setId(int id){

this->tutor_id=id;
}
int Email::getId(){
    return this->tutor_id;
}
