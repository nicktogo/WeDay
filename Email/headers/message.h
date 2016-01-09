#ifndef MESSAGE_H
#define MESSAGE_H

#include "part.h"
#include "multipart.h"
#include "emailinfo.h"
#include <QList>

class Message:public QObject
{
protected:
    emailInfo * sender;
    QList<emailInfo*>receiverTo,receiverCc,receiverBcc;
    QString subject;
    Part * content;
    Part::Encoding headEncoding;


public:

    enum ReceiverType{
        To,
        Cc,
        Bcc
    };

    Message(bool createAutoMimeContent=true);
    ~Message();


    void setSender(emailInfo * sender);
    void addReceiver(emailInfo * rece,ReceiverType=To);
    void addTo(emailInfo * rece);
    void addCc(emailInfo * rece);
    void addBcc(emailInfo * rece);
    void setSubject(const QString & subject);
    void addPart(Part *part);
    void setHeaderEncoding(Part::Encoding);

    const emailInfo & getSender() const;
    const QList<emailInfo*> & getReceivers(ReceiverType=To)const;
    const QString & getSubject()const;
    const QList<Part*> & getParts()const;

    Part& getContent();
    void setContent(Part *content);


    virtual QString toString();
};

#endif // MESSAGE_H
