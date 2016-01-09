#include "Classtable/headers/newclass.h"
#include "ui_newclass.h"
#include "Classtable/headers/newtutor.h"
#include "Classtable/headers/newpro.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
NewClass::NewClass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewClass)
{
    ui->setupUi(this);
    sendtype=-1;
    i=-1;j=-1;
    count=0;
    pn=new QMap<QString,int>();
    problem=new QList<Problem>();
    tutor=new QList<Tutor>();
    mail=new QList<Email>();
    assist=new QMap<int,int>();
    dp =new QList<Problem>;
     dt=new QList<int>;
    QStringList list=QStringList()<<"both"<<"single week"<<"double week";
    ui->comboBox_2->addItems((list));
    ui->comboBox_2->show();
}


NewClass::~NewClass()
{
    delete ui;
}
void NewClass::receivexy(int _i,int _j,int _count){
    i=_i;
    j=_j;
    count=_count;
    switch(i+1){
    case 1:ui->label_3->setText("Monday NO."+QString::number(j+1,10));break;
        case 2:ui->label_3->setText("Tuesday NO."+QString::number(j+1,10));break;
        case 3:ui->label_3->setText("Wednesday NO."+QString::number(j+1,10));break;
        case 4:ui->label_3->setText("Thursday NO."+QString::number(j+1,10));break;
        case 5:ui->label_3->setText("Friday NO."+QString::number(j+1,10));break;
        case 6:ui->label_3->setText("Saturday NO."+QString::number(j+1,10));break;
        case 7:ui->label_3->setText("Sunday NO."+QString::number(j+1,10));break;

    }



}

void NewClass::rec_tr(Tutor tr,QList<Email>*le){

    tr.setId(count);
    count++;
    tutor->append(tr);
    ui->comboBox->addItem(tr.getName());
    ui->comboBox->show();
    for(int i=0;i<le->count();i++) {
        ((Email)(le->at(i))).setId(tr.getId());
        Email e(((Email)(le->at(i))).getAdd());
       e.setId(tr.getId());
        mail->append( e);

      }
}
void NewClass::rec_pr(QList<Problem>*lp){


    for(int i=0;i<lp->count();i++) {

  //      Problem p(((Problem)(lp->at(i))).getTitle(),((Problem)(lp->at(i))).getType(),((Problem)(lp->at(i))).getTexe(),
   //               ((Problem)(lp->at(i))).getDdl(),((Problem)(lp->at(i))).getMail());

        problem->append(((Problem)(lp->at(i))));
        if(!pn->contains(((Problem)(lp->at(i))).getTitle())){
        ui->comboBox_6->addItem(((Problem)(lp->at(i))).getTitle());
        pn->insert(((Problem)(lp->at(i))).getTitle(),1);

        ui->comboBox_6->show();
}
    }
}

void NewClass::on_pushButton_2_clicked()
{
    NewTutor *ntr= new NewTutor(this);
     connect(ntr,SIGNAL(sendtr(Tutor,QList<Email>*)),this,SLOT(rec_tr(Tutor,QList<Email>*)));
    ntr->setWindowFlags(Qt::Dialog|Qt::CustomizeWindowHint);
    ntr->show();
}

void NewClass::on_pushButton_4_clicked()
{
    NewPro *np= new NewPro(this);
     connect(np,SIGNAL(sendpr(QList<Problem>*)),this,SLOT(rec_pr(QList<Problem>*)));
     connect(this,SIGNAL(sendmail(QList<Email>*)),np,SLOT(rec_mail(QList<Email>*)));
     emit sendmail(mail);
    np->setWindowFlags(Qt::Dialog|Qt::CustomizeWindowHint);
    np->show();
}

void NewClass::on_pushButton_clicked()
{

    if(ui->lineEdit_3->text()==NULL){


         QMessageBox::information(NULL, "!!!", "subject is null",0 ,0);
    }
    else{
        if(ui->lineEdit->text()==NULL){


             QMessageBox::information(NULL, "!!!", "teacher is null",0 ,0);
        }
        else{
            if(ui->lineEdit_2->text()==NULL){


                 QMessageBox::information(NULL, "!!!", "classroom is null",0 ,0);
            }
            else{
                if(sendtype==2){
                    for(int i=0;i<dt->count();i++){
                         QSqlQuery q;
                         q.exec("delete from tutor where id="+dt->at(i));
                    }
                /*    for(int i=0;i<dp->count();i++){
                         QSqlQuery q;
                         q.exec("delete from problem where title='"+((Problem)(dp->at(i))).getTitle()+"' and type ='"+((Problem)(dp->at(i))).getType()+"' and ddl ='"+
                                ((Problem)(dp->at(i))).getDdl()+"' and text='"+((Problem)(dp->at(i))).getTexe()+"' and mail='"+((Problem)(dp->at(i))).getMail()+"'");
                    }
                   */
                    QSqlQuery q,qd;
                    q.exec("select id from subject where week="+QString::number(j,10)+" and ttime="+QString::number(i,10)+" and tname='"+tname+"'");
                   q.first();
                    qd.exec("delete from problem where id="+q.value(0).toInt());


                    QSqlQuery query,q2,q3,q4,q5;
                    for(int j=0;j<tutor->count();j++){
                        q3.exec("update tutor set name='"+((Tutor)(tutor->at(i))).getName()+"' and set tel='"+((Tutor)(tutor->at(i))).getTel()+"' where id="+QString::number(((Tutor)(tutor->at(i))).getId(),10));



                    }

                     for(int ii=0;ii<problem->count();ii++){


                             q2.prepare("insert into problem (class_id int,title string,type int,text string,ttime string,mail string)");
                             q2.bindValue(0,q.value(0).toInt());
                             q2.bindValue(1,((Problem)(problem->at(ii))).getTitle());
                             q2.bindValue(2,((Problem)(problem->at(ii))).getType());
                             q2.bindValue(3,((Problem)(problem->at(ii))).getTexe());
                             q2.bindValue(4,((Problem)(problem->at(ii))).getDdl());
                             q2.bindValue(5,((Problem)(problem->at(ii))).getMail());
                             q2.exec();




                     }



                }else{

                Table t(ui->lineEdit_3->text(),ui->lineEdit->text(),j,i,ui->lineEdit_2->text(),ui->comboBox_2->currentText());
                emit sendtable(t,tutor,problem,mail);
                this->close();
                }

            }

        }


    }

}



void NewClass::on_comboBox_currentIndexChanged(const QString &arg1)
{
    ui->comboBox_3->clear();
    ui->comboBox_4->clear();
    int id=-1;
    for(int i=0;i<tutor->count();i++){
        if(((Tutor)(tutor->at(i))).getName()==arg1){

            ui->comboBox_3->addItem(((Tutor)(tutor->at(i))).getTel());
            ui->comboBox_3->show();
            id=((Tutor)(tutor->at(i))).getId();
            break;
        }
    }
    for(int i=0;i<mail->count();i++){
      if(((Email)(mail->at(i))).getId()==id){
          ui->comboBox_4->addItem(((Email)(mail->at(i))).getAdd());
          ui->comboBox_4->show();
      }
    }


}


void NewClass::on_comboBox_6_currentTextChanged(const QString &arg1)
{
    ui->comboBox_5->clear();
    for(int i=0;i<problem->count();i++){

       // Problem p(((Problem)(problem->at(i))).getTitle(),((Problem)(problem->at(i))).getType(),((Problem)(problem->at(i))).getTexe(),
        //          ((Problem)(problem->at(i))).getDdl(),((Problem)(problem->at(i))).getMail());

        if(((Problem)(problem->at(i))).getTitle()==arg1){
            QString type;
            switch (((Problem)(problem->at(i))).getType()) {
            case 0:type="Finally Test";

                break;
            case 1:type="Midlle Test";

                break;
            case 2:type="Other Test";

                break;

            }

            ui->label_17->setText(type);
            ui->label_15->setText(((Problem)(problem->at(i))).getDdl());
            if(((Problem)(problem->at(i))).getMail()!=NULL){
            ui->comboBox_5->addItem(((Problem)(problem->at(i))).getMail());
            ui->comboBox_5->show();
            }
        }



    }
}

void NewClass::on_pushButton_3_clicked()
{
    //sen to mail   mail=ui->comboBox_5->currentText()
}

void NewClass::on_comboBox_6_currentIndexChanged(const QString &arg1)
{

}

void NewClass::on_pushButton_5_clicked()
{
    if(ui->comboBox->currentText()==NULL){


         QMessageBox::information(NULL, "!!!", "no tutor",0 ,0);
    }
    else{
      for(int i=0;i<tutor->count();i++){
        if(((Tutor)(tutor->at(i))).getName()==ui->comboBox->currentText()){
            int id=((Tutor)(tutor->at(i))).getId();
             for(int j=0;j<mail->count();j++){
                if(((Email)(mail->at(j))).getId()==id){
                    mail->removeAt(j);
                }
            }

            tutor->removeAt(i);
            ui->comboBox->removeItem(ui->comboBox->currentIndex());
            break;
        }

      }

    }
}

void NewClass::on_pushButton_6_clicked()
{
    if(ui->comboBox_6->currentText()==NULL){


         QMessageBox::information(NULL, "!!!", "no problem",0 ,0);
    }
    else{
      for(int i=0;i<problem->count();i++){
          if(((Problem)(problem->at(i))).getTitle()==ui->comboBox_6->currentText()){
              problem->removeAt(i);

        }

      }
      ui->comboBox_6->removeItem(ui->comboBox_6->currentIndex());

    }
}
void NewClass::rec_type(int i,int j,int type,QString _tname) {
    tname=_tname;
if(type==1){
ui->pushButton->hide();
ui->pushButton_2->hide();
ui->pushButton_4->hide();
ui->pushButton_5->hide();
ui->pushButton_6->hide();
ui->pushButton_7->hide();
ui->pushButton_8->hide();
}
QSqlQuery query,q2,q3,q4,q5;
QString subname,teacher,classroom,ttype;
int week,time,id;
time=i;
week=j;
sendtype=type;
switch(i+1){
case 1:ui->label_3->setText("Monday NO."+QString::number(j+1,10));break;
    case 2:ui->label_3->setText("Tuesday NO."+QString::number(j+1,10));break;
    case 3:ui->label_3->setText("Wednesday NO."+QString::number(j+1,10));break;
    case 4:ui->label_3->setText("Thursday NO."+QString::number(j+1,10));break;
    case 5:ui->label_3->setText("Friday NO."+QString::number(j+1,10));break;
    case 6:ui->label_3->setText("Saturday NO."+QString::number(j+1,10));break;
    case 7:ui->label_3->setText("Sunday NO."+QString::number(j+1,10));break;

}
    query.exec("select name,teacher,id,classroom,type from subject where tname='"+tname+"' and time="+i+" and week="+j);

query.first();

    if(query.next())
    {


        qDebug() << query.value(0).toString() << query.value(1).toString()<<query.value(2).toString()<<query.value(3).toString();
        subname=query.value(0).toString();
        teacher=query.value(1).toString();


        id=query.value(2).toInt();
        classroom=query.value(3).toString();
        ttype=query.value(4).toString();
        ui->comboBox_2->clear();
        ui->comboBox_2->addItem(ttype);
        ui->comboBox_2->show();
        ui->lineEdit_3->setText(subname);
        ui->lineEdit->setText(teacher);
        ui->lineEdit_2->setText(classroom);

        q2.exec("select tutor_id from assist where class_id="+id);

        q2.first();
        do{
            q3.exec("select name,tel from tutor where id="+q2.value(0).toInt());

            if(q3.first()){
                Tutor tr(q3.value(0).toString(),q3.value(1).toString());
                tr.setId(q2.value(0).toInt());

                tutor->append(tr);
                ui->comboBox->addItem(tr.getName());
                ui->comboBox->show();
                q4.exec("select mail from mail where tutor_id="+q2.value(0).toInt());
                q4.first();
                do {

                    Email e(q4.value(0).toString());
                   e.setId(q2.value(0).toInt());
                    mail->append( e);

                }while(q4.next());


            }


        }while(q2.next());
        q5.exec("select title,type,time,text,mail from problem where class_id="+id);
        q5.first();
        do{
            Problem p(id,q5.value(0).toString(),q5.value(1).toInt(),q5.value(2).toString(),
                      q5.value(3).toString(),q5.value(4).toString());
            ui->comboBox_6->addItem(q5.value(0).toString());
            problem->append(p);
        }while(q5.next());



    }


}

void NewClass::on_pushButton_7_clicked()
{
    if(ui->comboBox->currentText()==NULL){
         QMessageBox::information(NULL, "!!!", "no tutor",0 ,0);

    }else{
        int i,id;
        QList<Email> *e=new QList<Email>;
        for(i=0;i<tutor->count();i++){
            if(((Tutor)(tutor->at(i))).getName()==ui->comboBox->currentText()){


                id=((Tutor)(tutor->at(i))).getId();
                break;
            }
        }
        int j=0,c=mail->count(),k=0;
        while(j<c){
          if(((Email)(mail->at(k))).getId()==id){
              e->append(((Email)(mail->at(k))));
              mail->removeAt(k);
              k--;

          }
          k++;
          j++;
        }
        NewTutor *nt =new NewTutor();
        connect(this,SIGNAL(sendtr(Tutor,QList<Email>*)),nt,SLOT(rec_tr(Tutor,QList<Email>*)));
        connect(nt,SIGNAL(sendtr(Tutor,QList<Email>*)),this,SLOT(rec_tr(Tutor,QList<Email>*)));
        emit sendtr(((Tutor)(tutor->at(i))),e);
        tutor->removeAt(i);
        count--;
        ui->comboBox->removeItem(ui->comboBox->currentIndex());
        nt->setWindowFlags(Qt::Dialog|Qt::CustomizeWindowHint);

        nt->show();



    }
}

void NewClass::on_pushButton_8_clicked()
{
    if(ui->comboBox_6->currentText()==NULL){
         QMessageBox::information(NULL, "!!!", "no problem",0 ,0);

    }else{
        QList<Email> *e=new QList<Email>;
        Problem *p;
       int pos=-1,i=0,c,k=0;
       c=problem->count();

        while(k<c){


            if(((Problem)(problem->at(i))).getTitle()==ui->comboBox_6->currentText()){
                Email m(((Problem)(problem->at(i))).getMail());
                e->append(m);
                p=new Problem(((Problem)(problem->at(i))).getTitle(),((Problem)(problem->at(i))).getType(),((Problem)(problem->at(i))).getTexe(),
                          ((Problem)(problem->at(i))).getDdl(),((Problem)(problem->at(i))).getMail());

                 problem->removeAt(i);
                i--;





            }
            k++;
            i++;
        }
        NewPro *np=new NewPro();


        connect(this,SIGNAL(sendp(QList<Email>*,Problem*)),np,SLOT(rec_p(QList<Email>*,Problem*)));
        connect(np,SIGNAL(sendpr(QList<Problem>*)),this,SLOT(rec_pr(QList<Problem>*)));
        connect(this,SIGNAL(sendmail(QList<Email>*)),np,SLOT(rec_mail(QList<Email>*)));
        emit sendp(e,p);
        emit sendmail(mail);
        pn->remove(p->getTitle());
       ui->comboBox_6->removeItem(ui->comboBox_6->currentIndex());
       np->setWindowFlags(Qt::Dialog|Qt::CustomizeWindowHint);
       np->show();

    }
}

void NewClass::rec_tpe(Table c,QList<Tutor>* t,QList<Problem>* p,QList<Email>* e){

    switch(c.getWeek()+1){
    case 1:ui->label_3->setText("Monday NO."+QString::number(c.getTime()+1,10));break;
        case 2:ui->label_3->setText("Tuesday NO."+QString::number(c.getTime()+1,10));break;
        case 3:ui->label_3->setText("Wednesday NO."+QString::number(c.getTime()+1,10));break;
        case 4:ui->label_3->setText("Thursday NO."+QString::number(c.getTime()+1,10));break;
        case 5:ui->label_3->setText("Friday NO."+QString::number(c.getTime()+1,10));break;
        case 6:ui->label_3->setText("Saturday NO."+QString::number(c.getTime()+1,10));break;
        case 7:ui->label_3->setText("Sunday NO."+QString::number(c.getTime()+1,10));break;

    }

            ui->comboBox_2->clear();
            ui->comboBox_2->addItem(c.getType());
            ui->comboBox_2->show();
            ui->lineEdit_3->setText(c.getClassname());
            ui->lineEdit->setText(c.getTeacher());
            ui->lineEdit_2->setText(c.getClassroom());

           for(int k=0;k<t->count();k++){


                    tutor->append((Tutor)(t->at(k)));
                    ui->comboBox->addItem(((Tutor)(t->at(k))).getName());
                    ui->comboBox->show();
                    for(int v=0;v<e->count();v++){
                        mail->append(( Email)(e->at(v)));
                        }
           }

              for(int k=0;k<p->count();k++){
                problem->append((Problem)(p->at(k)));
                if(!pn->contains(((Problem)(p->at(k))).getTitle())){

                    ui->comboBox_6->addItem(((Problem)(p->at(k))).getTitle());
                    pn->insert(((Problem)(p->at(k))).getTitle(),1);
                }
              }
count=tutor->count();

}
