#include "Classtable/headers/newpro.h"
#include "ui_newpro.h"
#include <QDate>
#include <QCalendarWidget>
#include <QMessageBox>
#include <QStringList>
#include <QStandardItemModel>
NewPro::NewPro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewPro)
{
    ui->setupUi(this);
    problem=new QList<Problem>();
    mail=new QList<Email>();
    ui->calendarWidget->hide();
    QStringList list=QStringList()<<"Finally test"<<"Middle test"<<"Other test";
    ui->comboBox->addItems(list);
    ui->comboBox->show();
   QDateTime data = QDateTime::currentDateTime();
    ui->label_8->setText(data.toString("yyyy-MM-dd"));

     standardItemModel = new QStandardItemModel(this);
}

NewPro::~NewPro()
{
    delete ui;
}

void NewPro::on_pushButton_clicked()
{
    if(ui->lineEdit_2->text()==NULL){
        QMessageBox::information(NULL, "!!!", "title is null",0 ,0);
      }
    else{
        if(standardItemModel->rowCount()==0){
            Problem p(ui->lineEdit_2->text(),ui->comboBox->currentIndex(),ui->textEdit->toPlainText(),ui->label_8->text(),"");
            problem->append(p);

        }
        for(int i=0;i<standardItemModel->rowCount();i++){


          QStandardItem *item=standardItemModel->item(i);


         Problem p(ui->lineEdit_2->text(),ui->comboBox->currentIndex(),ui->textEdit->toPlainText(),ui->label_8->text(),item->text());
         problem->append(p);
        }

      emit sendpr(problem);
        this->close();

    }

}
void NewPro::rec_mail(QList<Email> *le){
    for(int i=0;i<le->count();i++){


                 QString s=((Email)(le->at(i))).getAdd();
                 ui->comboBox_2->addItem(s);
                 ui->comboBox_2->show();
}

}

void NewPro::itemClicked(QModelIndex index){
    //index.data().tostring()

}

void NewPro::on_pushButton_4_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::question(NULL, "!!", "Do you want to give up?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(rb == QMessageBox::Yes)
    {
      this->close();
    }

}

void NewPro::on_pushButton_5_clicked()
{


    ui->calendarWidget->show();
    connect(ui->calendarWidget,SIGNAL(clicked(QDate)),this,SLOT(getData()));

}

void NewPro::getData()
{
    QDate data = ui->calendarWidget->selectedDate();
    ui->label_8->setText(data.toString("yyyy-MM-dd"));
    ui->calendarWidget->hide();
}




void NewPro::on_pushButton_3_clicked()
{

       QString s=ui->comboBox_2->currentText();
       QStandardItem *item = new QStandardItem(s);

       standardItemModel->appendRow(item);

       ui->listView->setModel(standardItemModel);
       connect(ui->listView,SIGNAL(clicked(QModelIndex)),this,SLOT(itemClicked(QModelIndex)));

}

void NewPro::on_pushButton_6_clicked()
{
    if(ui->listView->currentIndex().row()==-1){


        QMessageBox::information(NULL, "!!!", "please choose one",0 ,0);

      }
    else{
        standardItemModel->removeRow(ui->listView->currentIndex().row());
    }

}
void NewPro::rec_p(QList<Email>* e,Problem* p){
    ui->lineEdit_2->setText(p->getTitle());
    ui->textEdit->setText(p->getTexe());
    ui->label_8->setText(p->getDdl());
    QString type;
    switch (p->getType()) {
    case 0:type="Finally Test";

        break;
    case 1:type="Midlle Test";

        break;
    case 2:type="Other Test";

        break;

    }
     ui->comboBox_2->setCurrentText(type);

    for(int i=0;i<e->count();i++){
        if(((Email)(e->at(i))).getAdd()!=NULL){
    QStandardItem *item = new QStandardItem(((Email)(e->at(i))).getAdd());

    standardItemModel->appendRow(item);

    ui->listView->setModel(standardItemModel);
    connect(ui->listView,SIGNAL(clicked(QModelIndex)),this,SLOT(itemClicked(QModelIndex)));
}
}
}
