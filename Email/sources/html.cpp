#include "Email/headers/html.h"

Html::Html(const QString &html):Text(html)
{
    this->contentType="text/html";
}

Html::~Html(){}

void Html::setHtml(const QString &html){
    this->text=html;
}

const QString & Html::getHtml()const{
    return text;
}

void Html::prepare(){
    Text::prepare();
}
