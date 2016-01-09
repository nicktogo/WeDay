#include "Email/headers/loginwindow.h"
#include "Email/headers/sendmail.h"
#include "Email/headers/email.h"
#include "ui_loginwindow.h"
#include "Email/headers/part.h"
#include <QErrorMessage>
#include <QMessageBox>
#include <iostream>

using namespace std;

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->pwdLE->setEchoMode(QLineEdit::Password);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_loginBT_clicked(){

    QString email=ui->emailLE->text();
    QString pwd=ui->pwdLE->text();
    QMessageBox msg(this);
    QStringList strlist = email.split("@");
    QString nName = strlist.at(0);
    QString emailtype = strlist.at(1);

    if(email.isEmpty()||pwd.isEmpty()){
        msg.setText("邮箱或密码不能为空！");
        msg.exec();
        ui->emailLE->setFocus();
        return;
    }

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


    SMTP smtp (host, port, SMTP::TcpConnection);
    if (!smtp.connectHost())
    {
        msg.setText("SMTP 链接失败.\n请确认SMTP服务器是否设置正确.");
        msg.exec();
        return;
    }
    if(!smtp.login(email,pwd)){
        msg.setText("dengluoshiban！");
        msg.exec();
        return;
    }
    this->hide();
    em=new Email(0,nName,email,pwd);
    em->show();
    return;
}
