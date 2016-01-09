#include "Email/headers/multipart.h"
#include <QTime>
#include<QCryptographicHash>

const QString NameofMultiparts[]={
    "multipart/mixed",         //    Mixed
    "multipart/digest",        //    Digest
    "multipart/alternative",   //    Alternative
    "multipart/related",       //    Related
    "multipart/report",        //    Report
    "multipart/signed",        //    Signed
    "multipart/encrypted"      //    Encrypted
};


Multipart::Multipart(MultiPartType type)
{
    this->type=type;
    this->contentType=NameofMultiparts[this->type];
    this->contentEncoding=_8Bit;

    QCryptographicHash md5(QCryptographicHash::Md5);
    md5.addData(QByteArray().append(qrand()));
    contentBoundary=md5.result().toHex();
}

Multipart::~Multipart(){}

void Multipart::addPart(Part *part){
    parts.append(part);
}

const QList<Part*> & Multipart:: getParts()const{
    return parts;
}

void Multipart::setType(const MultiPartType type){
    this->type=type;
    this->contentType=NameofMultiparts[this->type];
}

Multipart::MultiPartType Multipart::getType()const{
    return type;
}

void Multipart::prepare(){
    QList<Part*>::iterator it;
    content="";

    for(it=parts.begin();it!=parts.end();it++){
        content+= "--"+contentBoundary+"\r\n";
        (*it)->prepare();
        content+=(*it)->toString();
    };
    content+="--"+contentBoundary+"--\r\n";
    Part::prepare();
}


