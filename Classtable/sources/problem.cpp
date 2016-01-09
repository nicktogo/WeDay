#include "Classtable/headers/problem.h"

Problem::Problem()
{

}
void Problem::copy(Problem p)
{

    this->title=p.getTitle();
    this->type=p.getType();
    this->text=p.getTexe();
    this->ddl=p.getDdl();
    this->mail=p.getMail();
}
Problem::Problem(int _id,QString _title,int _type,QString _text,QString _ddl,QString _mail)
{
    this->id=_id;
    this->title=_title;
    this->text=_text;
    this->ddl=_ddl;
    this->mail=_mail;
    this->type=_type;

}

Problem::Problem(QString _title,int _type,QString _text,QString _ddl,QString _mail)
{

    this->title=_title;
    this->text=_text;
    this->ddl=_ddl;
    this->mail=_mail;
    this->type=_type;

}
QString Problem::getTitle(){
    return this->title;
}
int Problem::getType(){
    return this->type;
}
QString Problem::getTexe(){
    return this->text;
}
QString Problem::getDdl(){
    return this->ddl;
}
QString Problem::getMail(){
    return this->mail;
}
void Problem::setId(int id){
    this->id=id;
}
int Problem::getId(){
    return this->id;
}
