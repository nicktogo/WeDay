#ifndef HTML_H
#define HTML_H

#include "text.h"

class Html:public Text
{
    Q_OBJECT
protected:
    virtual void prepare();

public:
    Html(const QString &html="");
    ~Html();

    void setHtml(const QString & html);
    const QString& getHtml() const;
};

#endif // HTML_H
