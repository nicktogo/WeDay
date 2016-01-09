#ifndef INLINEFILE_H
#define INLINEFILE_H

#include "file.h"

class Inlinefile:public File
{
protected:
    virtual void prepare();
public:
    Inlinefile(QFile *file);
    ~Inlinefile();
};

#endif // INLINEFILE_H
