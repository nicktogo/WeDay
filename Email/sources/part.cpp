#include "Email/headers/part.h"
#include "Email/headers/quotedprintable.h"

Part::Part()
{
    contentEncoding=_7Bit;
    prepared=false;
    contentBoundary="";
}

Part::~Part(){return;}

void Part::setHeader(const QString & header)
{
    this->header = header;
}

const QString& Part::getHeader() const
{
    return header;
}

void Part::setContent(const QByteArray & content)
{
    this->content = content;
}

const QByteArray& Part::getContent() const
{
    return content;
}

void Part::addHeaderLine(const QString & line)
{
    this->header += line + "\r\n";
}

void Part::setContentType(const QString & contentType)
{
    this->contentType = contentType;
}

const QString & Part::getContentType() const
{
    return this->contentType;
}

void Part::setCharset(const QString & contentcharset)
{
    this->contentCharset = contentcharset;
}

const QString & Part::getCharset() const
{
    return this->contentCharset;
}

void Part::setContentId(const QString & contentId)
{
    this->contentId = contentId;
}

const QString & Part::getContentId() const
{
    return this->contentId;
}

void Part::setContentName(const QString & contentName)
{
    this->contentName = contentName;
}

const QString & Part::getContentName() const
{
    return this->contentName;
}

void Part::setEncoding(Encoding encode)
{
    this->contentEncoding = encode;
}

Part::Encoding Part::getEncoding() const
{
    return this->contentEncoding;
}

ContentFormat& Part::getContentFormat()
{
    return this->format;
}

QString Part::toString()
{
    if (!prepared)
        prepare();

    return mimeString;
}

void Part::prepare(){
    mimeString=QString();

    mimeString.append("content-Type: ").append(contentType);

    if(contentName!="")
        mimeString.append("; name=\"").append(contentName).append("\"");
    if(contentCharset!="")
        mimeString.append("; charset=").append(contentCharset);
    if(contentBoundary!="")
        mimeString.append("; boundary=").append(contentBoundary);

    mimeString.append("\r\n");

    mimeString.append("Content-Transfer-Encoding: ");
    switch (contentEncoding) {
    case _7Bit:
        mimeString.append("7bit\r\n");
        break;
    case _8Bit:
        mimeString.append("8bit\r\n");
        break;
    case Base64:
        mimeString.append("base64\r\n");
        break;
    case QuotedPrintable:
        mimeString.append("quoted-printable\r\n");
        break;
    }

    if(contentId!=NULL)
        mimeString.append("Content-ID: <").append(contentId).append(">\r\n");

    mimeString.append(header).append("\r\n");


    switch(contentEncoding){
    case _7Bit:
        mimeString.append(QString(content).toLatin1());
        break;
    case _8Bit:
        mimeString.append(content);
        break;
    case Base64:
        mimeString.append(format.format(content.toBase64()));
        break;
    case QuotedPrintable:
        mimeString.append(format.format(QuotedPrintable::encode(content),true));
        break;
    }

    mimeString.append("\r\n");

    prepared=true;

}
