#include "Email/headers/message.h"

#include <QDateTime>
#include <typeinfo>
#include "Email/headers/quotedprintable.h"


Message::Message(bool createAutoMimeContent):
    headEncoding(Part::_8Bit)
{
    if(createAutoMimeContent)
        this->content=new Multipart();
}

Message::~Message(){}

Part & Message::getContent(){
    return *content;
}

void Message::setContent(Part *content){
    this->content=content;
}

void Message::setSender(emailInfo *sender){
    this->sender=sender;
}

const emailInfo & Message::getSender()const{
    return *sender;
}


void Message::addReceiver(emailInfo *rece, ReceiverType type){
    switch(type){
    case To:
        receiverTo<<rece;
        break;
    case Cc:
        receiverCc<<rece;
        break;
    case Bcc:
        receiverBcc<<rece;
        break;
    }
}

const QList<emailInfo*> & Message::getReceivers(ReceiverType type)const{
    switch (type) {
    case To:
        return receiverTo;
        break;
    case Cc:
        return receiverCc;
        break;
    case Bcc:
        return receiverBcc;
        break;
    }
}

void Message::addTo(emailInfo *rece){
    this->receiverTo<<rece;
}

void Message::addCc(emailInfo *rece){
    this->receiverCc<<rece;
}

void Message::addBcc(emailInfo *rece){
    this->receiverBcc<<rece;
}

void Message::setSubject(const QString &subject){
    this->subject=subject;
}

const QString & Message::getSubject()const{
    return subject;
}

void Message::addPart(Part *part){
    if(typeid(*content)==typeid(Multipart)){
        ((Multipart*)content)->addPart(part);
    };
}

const QList<Part*> & Message::getParts()const{
    if(typeid(*content)==typeid(Multipart)){
        return ((Multipart*)content)->getParts();
    }
    else{
        QList<Part*>*mulparts=new QList<Part*>();
        mulparts->append(content);
        return *mulparts;
    }
}

void Message::setHeaderEncoding(Part::Encoding headEncoding){
    this->headEncoding=headEncoding;
}

//transfer the content of email to 'string'

QString Message::toString(){

    QString MIME;

    MIME="From:";
    if(sender->getUsername()!=""){
        switch(headEncoding){
        case Part::Base64:
            MIME += " =?utf-8?B?"+QByteArray().append(sender->getUsername()).toBase64()+"?=";
            break;
        case Part::QuotedPrintable:
            MIME += " =?utf-8?Q?"+QuotedPrintable::encode(QByteArray().append(sender->getUsername())).replace(' ', "_").replace(':',"=3A") + "?=";
            break;
        default:
            MIME += " "+sender->getUsername();
        }
    }
    MIME +=" <"+sender->getAddress()+">\r\n";

    MIME += "To:";
    QList<emailInfo*>::iterator it;
    int i;
    for(i=0,it=receiverTo.begin();it!=receiverTo.end();++it,++i){
        if(i!=0){
            MIME += ",";
        }
        if((*it)->getUsername()!=""){
            switch(headEncoding){
            case Part::Base64:
                MIME += " =?utf-8?B?"+QByteArray().append((*it)->getUsername()).toBase64()+"?=";
                break;
            case Part::QuotedPrintable:
                MIME += " =?utf-8?Q?" + QuotedPrintable::encode(QByteArray().append((*it)->getUsername())).replace(' ', "_").replace(':',"=3A") + "?=";
                break;
            default:
                MIME += " "+(*it)->getUsername();
            }
        }
        MIME += " <" + (*it)->getAddress() + ">";
    }
    MIME+="\r\n";

    if(receiverCc.size()!=0){
        MIME+="Cc:";
    }
    for(i=0,it=receiverCc.begin();it!=receiverCc.end();++it,++i){
        if(i!=0){
            MIME += ",";
        }
        if((*it)->getUsername()!=""){
            switch(headEncoding){
            case Part::Base64:
                MIME += " =?utf-8?B?"+QByteArray().append((*it)->getUsername()).toBase64()+"?=";
                break;
            case Part::QuotedPrintable:
                MIME += " =?utf-8?Q?" + QuotedPrintable::encode(QByteArray().append((*it)->getUsername())).replace(' ', "_").replace(':',"=3A") + "?=";
                break;
            default:
                MIME += " "+(*it)->getUsername();
            }
        }
        MIME += " <" + (*it)->getAddress() + ">";
    }
    if(receiverCc.size()!=0){
        MIME+="\r\n";
    }


    MIME+="Subject: ";

    switch(headEncoding){
    case Part::Base64:
        MIME += " =?utf-8?B?"+QByteArray().append(subject).toBase64()+"?=";
        break;
    case Part::QuotedPrintable:
        MIME += " =?utf-8?Q?" + QuotedPrintable::encode(QByteArray().append(subject)).replace(' ', "_").replace(':',"=3A") + "?=";
        break;
    default:
        MIME += subject;
    }

    MIME+="\r\n";
    MIME+="MIME-Version: 1.0\r\n";

    MIME+=content->toString();
    return MIME;
}
