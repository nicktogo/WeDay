#include "Classtable/headers/newtutor.h"
#include "ui_newtutor.h"
#include<QMessageBox>
NewTutor::NewTutor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTutor)
{
    ui->setupUi(this);
    mail=new QList<Email>();

}

NewTutor::~NewTutor()
{
    delete ui;

}


void NewTutor::on_pushButton_clicked()
{
    QString tel="";
    if(ui->lineEdit->text()==NULL){
        QMessageBox::information(NULL, "!!!", "name is null",0 ,0);
      }
    else{
    QString name=ui->lineEdit->text();
    tel=ui->lineEdit_2->text();
    Tutor tr(name,tel);
    emit sendtr(tr,mail);
    this->close();

    }
}

void NewTutor::on_pushButton_3_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::question(NULL, "!!", "Do you want to give up?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(rb == QMessageBox::Yes)
    {
      this->close();
    }
}

void NewTutor::on_pushButton_2_clicked()
{
    if(ui->lineEdit_3->text()==NULL){
        QMessageBox::information(NULL, "!!!", "email is null",0 ,0);
      }
    else{
        if(ui->lineEdit->text()==NULL){
            QMessageBox::information(NULL, "!!!", "name is null",0 ,0);
          }
        else{
            ui->comboBox->addItem(ui->lineEdit_3->text());
             ui->comboBox->show();
             Email e(ui->lineEdit_3->text());
            mail->append(e);

        }


    }
}
void NewTutor::rec_tr(Tutor t,QList<Email>* e){
    ui->lineEdit->setText(t.getName());
    ui->lineEdit_2->setText(t.getTel());

    for(int i=0;i<e->count();i++){

        ui->comboBox->addItem(((Email)(e->at(i))).getAdd());
        mail->append(e->at(i));
    }


}

void NewTutor::on_pushButton_4_clicked()
{
    if(ui->comboBox->currentText()==NULL){
        QMessageBox::information(NULL, "!!!", "eamil is null",0 ,0);

    }else{
        for(int i=0;i<mail->count();i++){

            if(((Email)(mail->at(i))).getAdd()==ui->comboBox->currentText()){

                mail->removeAt(i);
                break;
            }
        }
        ui->comboBox->removeItem(ui->comboBox->currentIndex());



    }

}
