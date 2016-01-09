#include "Email/headers/email.h"
#include "ui_email.h"
#include <QFileDialog>
#include <QErrorMessage>
#include <QMessageBox>
#include <iostream>

#include <stdio.h>
#include <cstring>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

//wnniydhvojjbhhqx
using namespace std;

Email::Email(QWidget *parent,QString nickName,QString email,QString pwd): QWidget(parent),
    ui(new Ui::Email),nickName(nickName),email(email),pwd(pwd)
{
    ui->setupUi(this);
    ui->senderL->setVisible(false);
    ui->senderLE->setVisible(false);
    ui->recevierL->setVisible(false);
    ui->receiverLE->setVisible(false);
    ui->subjectL->setVisible(false);
    ui->subjectLE->setVisible(false);
    ui->contentTE->setVisible(false);
    ui->attachmentL->setVisible(false);
    ui->addBT->setVisible(false);
    ui->cleanBT->setVisible(false);
    ui->sendBT->setVisible(false);
    ui->receiveList->setVisible(false);
    ui->fileList->setVisible(false);
    ui->draftList->setVisible(false);
    ui->saveBT->setVisible(false);
    ui->welcome->setText("Welcome,"+this->nickName);
}


void Email::on_inboxBT_clicked(){
    ui->receiveList->clear();
    ui->receiveList->setVisible(true);
    ui->draftList->setVisible(false);
    ui->senderL->setVisible(false);
    ui->senderLE->setVisible(false);
    ui->recevierL->setVisible(false);
    ui->receiverLE->setVisible(false);
    ui->subjectL->setVisible(false);
    ui->subjectLE->setVisible(false);
    ui->contentTE->setVisible(false);
    ui->attachmentL->setVisible(false);
    ui->fileList->setVisible(false);
    ui->addBT->setVisible(false);
    ui->cleanBT->setVisible(false);
    ui->sendBT->setVisible(false);
    ui->saveBT->setVisible(false);

    QStringList strlist = email.split("@");
    QString emailtype = strlist.at(1);

    QString server;

    if(emailtype=="163.com"){
        server="pop3.163.com";
    }else if(emailtype=="126.com"){
        server="pop.126.com";
    }else if(emailtype=="139.com"){
        server="pop3.139.com";
    }else if(emailtype=="qq.com"){
        server="pop.qq.com";
    }else if(emailtype=="sohu.com"){
        server="pop3.sohu.com";
    }else if(emailtype=="sina.com"){
        server="pop3.sina.com.cn";
    }else if(emailtype=="yahoo.com"){
        server="pop.mail.yahoo.com.cn";
    }else if(emailtype=="gmail.com"){
        server="pop.gmail.com";
    }else if(emailtype=="tom.com"){
        server="pop.tom.com.cn";
    }

    pop=new pop3(server,email,pwd,this->ui);
    pop->username=this->email;
}


void Email::on_outboxBT_clicked(){
    ui->receiveList->setVisible(false);
    ui->draftList->setVisible(false);
    ui->senderL->setVisible(true);
    ui->senderLE->setVisible(true);
    ui->senderLE->setText(email);
    ui->recevierL->setVisible(true);
    ui->receiverLE->setVisible(true);
    ui->receiverLE->clear();
    ui->subjectL->setVisible(true);
    ui->subjectLE->setVisible(true);
    ui->subjectLE->clear();
    ui->contentTE->setVisible(true);
    ui->contentTE->clear();
    ui->attachmentL->setVisible(true);
    ui->addBT->setVisible(true);
    ui->fileList->setVisible(true);
    ui->fileList->clear();
    ui->cleanBT->setVisible(true);
    ui->sendBT->setVisible(true);
    ui->saveBT->setVisible(true);
}


emailInfo* Email::stringToEmail(const QString &string){

    int start=string.indexOf("<");
    int end=string.indexOf(">");

    if(start==-1){
        return new emailInfo(string);
    }
    else{
        return new emailInfo(string.mid(start+1,end-start-1),string.left(start));
    }
}

void Email::on_addBT_clicked(){
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    if (dialog.exec())
        ui->fileList->addItems(dialog.selectedFiles());
}

void Email::on_cleanBT_clicked(){
    ui->fileList->clear();
}

void Email::on_sendBT_clicked(){

    QMessageBox msg(this);
    QString receiver=ui->receiverLE->text().trimmed();
    if(receiver.isEmpty()){
        msg.setText("请填写\"收件人\".");
        msg.exec();
        ui->receiverLE->setFocus();
        return;
    }

    QStringList strlist = email.split("@");
    QString emailtype = strlist.at(1);

    QString host;
    int port=25;

    if(emailtype=="163.com"){
        host="smtp.163.com";
    }else if(emailtype=="126.com"){
        host="smtp.126.com";
    }else if(emailtype=="139.com"){
        host="smtp.139.com";
    }else if(emailtype=="qq.com"){
        host="smtp.qq.com";
    }else if(emailtype=="sohu.com"){
        host="smtp.sohu.com";
    }else if(emailtype=="sina.com"){
        host="smtp.sina.com.cn";
    }else if(emailtype=="yahoo.com"){
        host="smtp.yahoo.com";
    }else if(emailtype=="gmail.com"){
        host="smtp.gmail.com";
        port=587;
    }else if(emailtype=="tom.com"){
        host="smtp.tom.com.cn";
    }

    emailInfo * sender=stringToEmail(email);

    QString subject=ui->subjectLE->text();
    QString html=ui->contentTE->toHtml();

    SMTP smtp (host, port, SMTP::TcpConnection);

    Message message;

    message.setSender(sender);
    message.setSubject(subject);

    QStringList receiverList=ui->receiverLE->text().trimmed().split(";");

    while(receiverList.size()>0&&receiverList.last().trimmed().isEmpty()){
        receiverList.removeLast();
    }

    for(int i=0;i<receiverList.size();++i){
        message.addReceiver(stringToEmail(receiverList.at(i)));
    }

    Html content;
    content.setHtml(html);
    message.addPart(&content);

    for(int i=0;i<ui->fileList->count();++i){
        Attachment *attach =new Attachment(new QFile(ui->fileList->item(i)->text().toUtf8()));
        message.addPart(attach);
    }

    if (!smtp.connectHost())
    {
        msg.setText("SMTP 链接失败.\n请确认SMTP服务器是否设置正确.");
        msg.exec();
        return;
    }
    if(!smtp.login(email,pwd)){
        msg.setText("用户名或密码错误！");
        msg.exec();
        return;
    }
    if(!smtp.sendMail(message)){
        msg.setText("发送失败！");
        msg.exec();
        ui->receiverLE->setFocus();
        ui->receiverLE->selectAll();
        return;
    }else{
        msg.setText("发送成功！");
        msg.exec();
    }

    smtp.quit();
}


void Email::on_saveBT_clicked(){
    ///home/belle/LinuxProgram

    QString path="/home/belle/LinuxProgram/draft/"+nickName;
    char*  pathname=stringToChar(path);
    mkdir(pathname,0777);

    FILE * fd;

    char str[10000];


    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss ddd");
    QString file=path+"/"+current_date;
    char*  filename=stringToChar(file);
    fd = fopen(filename, "w+");
    QString emailinfo;
    emailinfo.append(ui->senderLE->text()).append("\n");
    emailinfo.append(ui->receiverLE->text()).append("\n");
    emailinfo.append(ui->subjectLE->text()).append("\n");
    for(int i=0;i<ui->fileList->count();i++){
        emailinfo.append(ui->fileList->item(i)->text()).append("*");
        QString dd=ui->fileList->item(i)->text();
    }
    emailinfo.append("\n");
    emailinfo.append(ui->contentTE->toPlainText()).append("\n");

    char *info=stringToChar(emailinfo);

    if (fd)
    {
      fputs(info, fd);
      fclose(fd);
    }
    QMessageBox msg(this);
    msg.setText("保存成功！");
    msg.exec();

    system("sync");

}


void Email::on_draftBT_clicked(){
    ui->receiveList->setVisible(false);
    ui->draftList->clear();
    ui->draftList->setVisible(true);

    ui->senderL->setVisible(false);
    ui->senderLE->setVisible(false);
    ui->recevierL->setVisible(false);
    ui->receiverLE->setVisible(false);
    ui->subjectL->setVisible(false);
    ui->subjectLE->setVisible(false);
    ui->contentTE->setVisible(false);
    ui->attachmentL->setVisible(false);
    ui->fileList->setVisible(false);
    ui->addBT->setVisible(false);
    ui->cleanBT->setVisible(false);
    ui->sendBT->setVisible(false);
    ui->saveBT->setVisible(false);

    drafts.clear();
    drsender.clear();
    drreceiver.clear();
    drsubject.clear();
    drcontents.clear();
    drattachment.clear();

    DIR *directory;

    struct dirent*Dirent;  //dirent是为了获取某个文件夹目录内容所使用的结构体，所以取出来的目录内容放在mydirent中
    QString path="/home/belle/LinuxProgram/draft/"+nickName;
    string pathname = path.toStdString();
    if((directory=opendir(pathname.c_str()))==NULL){    //打开这个文件夹
        QMessageBox msg(this);
        msg.setText("没有草稿！");
        msg.exec();
        return;
    }

    FILE * fd1;
    char str[10000];
    int numberOfFile=0;
    while((Dirent=readdir(directory))!=NULL){    //一条一条的读取文件夹中的内容
      if(Dirent->d_name[0]=='.')
               continue;
      drafts.append(Dirent->d_name);
      path="/home/belle/LinuxProgram/draft/"+nickName+"/"+Dirent->d_name;
      pathname = path.toStdString();
      fd1= fopen(pathname.c_str(), "r");
      int i=0;
      QString show;
      while (!feof(fd1))
      {
          fgets(str,1024,fd1);  //读取一行
          switch(i){
          case 0:
              drsender.append(charToString(str).simplified());
              break;
          case 1:
              drreceiver.append(charToString(str).simplified());
              show.append("To: ").append(charToString(str).simplified());
              break;
          case 2:
              drsubject.append(charToString(str).simplified());
              show.append("    Subject: ").append(charToString(str).simplified());
              break;
          case 3:
              drattachment.append(charToString(str).simplified());
              break;
          default:
              drcontents.append(charToString(str).simplified());
          }
          i++;
      }
      ui->draftList->addItem(show);
      if(numberOfFile%2==0)
          ui->draftList->item(numberOfFile)->setBackground(QColor::fromRgb(255,169,169,200));
      else
          ui->draftList->item(numberOfFile)->setBackground(QColor::fromRgb(115,203,219,200));
      ui->draftList->item(numberOfFile)->setForeground(QColor::fromRgb(255,255,255));
      numberOfFile++;
    }
    if(numberOfFile==0){
        QMessageBox msg(this);
        msg.setText("mei you cao gao o ~");
        msg.exec();
        return;
    }
}







void Email::on_draftList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous){

    ui->receiveList->setVisible(false);
    ui->draftList->setVisible(false);
    ui->senderL->setVisible(true);
    ui->senderLE->setVisible(true);
    ui->senderLE->clear();
    ui->senderLE->setVisible(true);
    ui->recevierL->setVisible(true);
    ui->receiverLE->setVisible(true);
    ui->receiverLE->clear();
    ui->subjectL->setVisible(true);
    ui->subjectLE->setVisible(true);
    ui->subjectLE->clear();
    ui->contentTE->setVisible(true);
    ui->contentTE->clear();
    ui->attachmentL->setVisible(true);
    ui->addBT->setVisible(true);
    ui->fileList->setVisible(true);
    ui->fileList->clear();
    ui->cleanBT->setVisible(true);
    ui->sendBT->setVisible(true);
    ui->saveBT->setVisible(true);

    if(current==Q_NULLPTR)return;

    for(int i=0;i<ui->draftList->count();i++){
        if (ui->draftList->item(i)==current){
            ui->senderLE->setText(drsender.at(i));
            ui->receiverLE->setText(drreceiver.at(i));
            ui->subjectLE->setText(drsubject.at(i));
            ui->contentTE->setText(drcontents.at(i));
            QString path="/home/belle/LinuxProgram/draft/"+nickName+"/"+drafts.at(i);
            string pathname = path.toStdString();
            remove(pathname.c_str());
            break;
        }
    }




}





void Email::on_receiveList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous){

    ui->receiveList->setVisible(false);
    ui->draftList->setVisible(false);
    ui->senderL->setVisible(true);
    ui->senderLE->setVisible(true);
    ui->senderLE->clear();
    ui->senderLE->setVisible(true);
    ui->recevierL->setVisible(true);
    ui->receiverLE->setVisible(true);
    ui->receiverLE->clear();
    ui->subjectL->setVisible(true);
    ui->subjectLE->setVisible(true);
    ui->subjectLE->clear();
    ui->contentTE->setVisible(true);
    ui->contentTE->clear();
    ui->attachmentL->setVisible(true);
    ui->addBT->setVisible(true);
    ui->fileList->setVisible(true);
    ui->fileList->clear();
    ui->cleanBT->setVisible(true);
    ui->sendBT->setVisible(true);
    ui->saveBT->setVisible(true);

    if(current==Q_NULLPTR)return;

   for(int i=0;i<ui->receiveList->count();i++){
        if (ui->receiveList->item(i)==current){
            ui->senderLE->setText(pop->fromlist.at(i));
            ui->receiverLE->setText(pop->tolist.at(i));
            ui->subjectLE->setText(pop->subjectlist.at(i));
            ui->contentTE->setText(pop->contentlist.at(i));
            break;
        }
    }
}





QString Email::charToString(char *ch){
    QString result=QString(QLatin1String(ch));
    return result;
}

char* Email::stringToChar(QString str){
    char *result;
    QByteArray ba=str.toLatin1();
    result=ba.data();
    return result;
}


const QString Email::getEmail() const{
    return this->email;
}

void Email::setEmail(QString &email){
    this->email=email;
}

const QString Email::getNickName()const{
    return this->nickName;
}
void Email::setNickName(QString &nickName){
    this->nickName=nickName;
}
