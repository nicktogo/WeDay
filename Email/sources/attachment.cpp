#include "Email/headers/attachment.h"
#include<QFileInfo>

Attachment::Attachment(QFile *file)
    :File(file) {}
Attachment::~Attachment(){}

void Attachment::prepare(){
    this->header += "Content-disposition: attachment\r\n";
    File::prepare();
}
