#include "Email/headers/contentformat.h"

ContentFormat::ContentFormat(int maxLineLength):
    maxLineLength(maxLineLength){}

int ContentFormat::getMaxLineLength()const{
    return maxLineLength;
}

void ContentFormat::setMaxLineLength(int maxLength){
    maxLineLength=maxLength;
}

QString ContentFormat::format(const QString &content, bool quotedPrintable) const{
    QString showcontent;

    int numofchar=0;
    for(int i=0;i<content.length();++i){
        numofchar++;
        if(!quotedPrintable){
            if(numofchar>maxLineLength){
                showcontent.append("\r\n");
                numofchar=1;
            }
        }
        else{
            if(content[i]=='\n'){
                showcontent.append(content[i]);
                numofchar=0;
                continue;
            }
            if((numofchar>maxLineLength-1)||
                    ((content[i]=='=')&&(numofchar>maxLineLength-3))){
                showcontent.append('=');
                showcontent.append("\r\n");
                numofchar=1;
            }
        }
        showcontent.append(content[i]);
    }
    return showcontent;
}
