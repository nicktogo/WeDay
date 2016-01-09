#include "Email/headers/file.h"
#include <QFileInfo>

File::File(QFile *file)
{
    this->file=file;
    this->contentType="application/octet-stream";
    this->contentName=QFileInfo(*file).fileName();
    this->contentEncoding=Base64;
}

File::~File(){
    delete file;
}


void File::prepare(){

    file->open(QIODevice::ReadOnly);
    this->content=file->readAll();
    file->close();
    Part::prepare();
}
