#ifndef SENDMAIL_H
#define SENDMAIL_H

#include <QWidget>

namespace Ui {
class sendMail;
}

class sendMail : public QWidget
{
    Q_OBJECT
public:
    explicit sendMail(QWidget *parent = 0);

signals:

public slots:
private:
    Ui::sendMail *ui;
};

#endif // SENDMAIL_H
