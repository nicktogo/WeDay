#ifndef MULTIPART_H
#define MULTIPART_H

#include "part.h"

class Multipart:public Part
{
    Q_OBJECT

public:

    enum MultiPartType {
        Mixed           = 0,            // RFC 2046, section 5.1.3
        Digest          = 1,            // RFC 2046, section 5.1.5
        Alternative     = 2,            // RFC 2046, section 5.1.4
        Related         = 3,            // RFC 2387
        Report          = 4,            // RFC 6522
        Signed          = 5,            // RFC 1847, section 2.1
        Encrypted       = 6             // RFC 1847, section 2.2
    };


    Multipart(const MultiPartType type=Related);
    ~Multipart();

    void setType(const MultiPartType type);
    MultiPartType getType()const;

    void addPart(Part *part);
    const QList<Part*> & getParts()const;

    virtual void prepare();


protected:
    QList<Part*> parts;
    MultiPartType type;
};

#endif // MULTIPART_H
