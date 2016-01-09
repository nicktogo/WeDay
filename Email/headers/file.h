#ifndef FILE_H
#define FILE_H

#include "part.h"
#include<QFile>


class File:public Part
{
protected:
    QFile *file;
    virtual void prepare();
public:
    File(QFile *file);
    ~File();
};

#endif // FILE_H
