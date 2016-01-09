#include "Classtable/headers/assist.h"

Assist::Assist()
{

}
Assist::Assist(int cid,int tid)

{

    this->class_id=cid;
    this->tutor_id=tid;
}
int Assist::getCid(){
    return this->class_id;

}

int Assist::getTid(){
    return this->tutor_id;
}
