#ifndef PART_H
#define PART_H

#include <QObject>
#include "contentformat.h"

class Part:public QObject
{
    Q_OBJECT


public:
    Part();
    ~Part();

    enum Encoding {
        _7Bit,
        _8Bit,
        Base64,
        QuotedPrintable
    };



    const QString& getHeader() const;
    const QByteArray& getContent() const;

    void setContent(const QByteArray & content);
    void setHeader(const QString & header);

    void addHeaderLine(const QString & line);

    void setContentType(const QString & contentType);
    const QString & getContentType() const;

    void setCharset(const QString & contentcharset);
    const QString & getCharset() const;

    void setContentId(const QString & contentId);
    const QString & getContentId() const;

    void setContentName(const QString & contentName);
    const QString & getContentName() const;


    void setEncoding(Encoding encode);
    Encoding getEncoding() const;

    ContentFormat& getContentFormat();

    virtual QString toString();

    virtual void prepare();

protected:

    QString header;
    QByteArray content;

    QString contentType;
    QString contentCharset;
    QString contentId;
    QString contentName;
    QString contentBoundary;
    Encoding contentEncoding;

    QString mimeString;
    bool prepared;

    ContentFormat format;


};

#endif // PART_H
