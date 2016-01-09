#ifndef TEXT_H
#define TEXT_H

#include"part.h"

class Text:public Part
{
protected:
    QString text;
    void prepare();

public:
    Text(const QString &text="");
    ~Text();

    void setText(const QString & text);
    const QString & getText()const;
};

#endif // TEXT_H
