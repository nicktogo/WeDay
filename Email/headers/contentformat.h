#ifndef CONTENTFORMAT_H
#define CONTENTFORMAT_H

#include <QObject>
#include <QByteArray>

class ContentFormat:public QObject
{
    Q_OBJECT
private:
    int maxLineLength;

public:
    ContentFormat(int maxLineLength=80);

    int getMaxLineLength()const;
    void setMaxLineLength(int maxLength);

    QString format(const QString & content,bool quotedPrintable = false)const;
};

#endif // CONTENTFORMAT_H
