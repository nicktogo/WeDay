#include "Email/headers/text.h"

Text::Text(const QString & text)
{
    this->text=text;
    this->contentType="text/plain";
    this->contentCharset="utf-8";
    this->contentEncoding=_8Bit;
}

Text::~Text(){}

void Text::setText(const QString &text){
    this->text=text;
}

const QString & Text::getText()const{
    return text;
}

void Text::prepare(){
    this->content.clear();
    this->content.append(text);

    Part::prepare();
}

