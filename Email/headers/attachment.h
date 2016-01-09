#ifndef ATTACHMENT_H
#define ATTACHMENT_H

#include<QFile>
#include"part.h"
#include"file.h"


class Attachment:public File
{
    Q_OBJECT
protected:
    virtual void prepare();
public:
    Attachment(QFile *file);
    ~Attachment();
};

#endif // ATTACHMENT_H
