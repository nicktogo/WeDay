#include "Email/headers/sendmail.h"
#include "ui_sendmail.h"


sendMail::sendMail(QWidget *parent) : QWidget(parent),
    ui(new Ui::sendMail)
{
    ui->setupUi(this);
}
