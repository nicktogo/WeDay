#include "Email/headers/emailinfo.h"

emailInfo::emailInfo(const QString & address,const QString & username)
{
    this->address=address;
    this->username=username;
}

emailInfo::~emailInfo(){}


const QString & emailInfo::getAddress()const{
    return address;
}

const QString & emailInfo::getUsername()const{
    return username;
}


void emailInfo::setAddress(const QString &address){
    this->address=address;
}

void emailInfo::setUsername(const QString &username){
    this->username=username;
}
