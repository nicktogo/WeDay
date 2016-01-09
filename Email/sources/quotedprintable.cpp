#include "Email/headers/quotedprintable.h"

QString & QuotedPrintable::encode(const QByteArray & input){
    QString * encodeout=new QString();

    char byte;
    const char hex[]={'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    for (int i = 0; i < input.length() ; ++i)
    {
        byte = input[i];

        if ((byte == 0x20) || (byte >= 33) && (byte <= 126) && (byte != 61))
        {
            encodeout->append(byte);
        }
        else
        {
            encodeout->append('=');
            encodeout->append(hex[((byte >> 4) & 0x0F)]);
            encodeout->append(hex[(byte & 0x0F)]);
        }
    }

    return *encodeout;
}

QByteArray & QuotedPrintable::decode(const QString & input){
    const int hexVal[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0, 0, 10, 11, 12, 13, 14, 15};
    QByteArray *codeout = new QByteArray();

    for (int i = 0; i < input.length(); ++i)
    {

        if (input.at(i).toLatin1() == '=')
        {
            codeout->append((hexVal[input.at(++i).toLatin1() - '0'] << 4) + hexVal[input.at(++i).toLatin1() - '0']);
        }
        else
        {
            codeout->append(input.at(i).toLatin1());
        }
    }

    return *codeout;
}


