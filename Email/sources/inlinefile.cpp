#include "Email/headers/inlinefile.h"

Inlinefile::Inlinefile(QFile *file)
    :File(file) {}

Inlinefile::~Inlinefile() {}

void Inlinefile::prepare(){
    this->header += "Content-Disposition: inline\r\n";
    File::prepare();
}
