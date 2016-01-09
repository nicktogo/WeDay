#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <qmessagebox.h>
#include "sendmail.h"
#include "email.h"
#include "mimesmtp.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();


private slots:
    void on_loginBT_clicked();

private:
    Ui::LoginWindow *ui;
    sendMail s;
    Email *em;
};

#endif // LOGINWINDOW_H
