#include "Classtable/headers/newtable.h"
#include "ui_newtable.h"
#include "Classtable/headers/newclass.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QMenu>
NewTable::NewTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTable)
{
    ui->setupUi(this);
    copyok=false;
    table= new QList<Table>();
    problem=new QList<Problem>();
    tutor=new QList<Tutor>();
    mail=new QList<Email>();
    assist=new QList<Assist> ;

    cproblem=new QList<Problem>();
    ctutor=new QList<Tutor>();
    cmail=new QList<Email>();
    cassist=new QList<Assist> ;

    ini_table();
    for(int i=0;i<11;i++)
        for(int j=0;j<7;j++) pos[i][j]=-1;
    ui->tableWidget->setMouseTracking(true);
    connect(ui->tableWidget,SIGNAL(cellEntered(int , int) ),this,SLOT( getxy(int, int) ) );

}

NewTable::~NewTable()
{
    delete ui;
}


void NewTable::contextMenuEvent(QContextMenuEvent *event){
        QMenu *menu=new QMenu();
        QCursor cur=this->cursor();
        QAction *copy=new QAction("copy",this);
        menu->addAction(copy);
        connect(copy,SIGNAL(triggered()),this,SLOT(copy()));
        QAction *paste=new QAction("paste",this);
        menu->addAction(paste);
        connect(paste,SIGNAL(triggered()),this,SLOT(paste()));
        if(!copyok) paste->setEnabled(false);
                else paste->setEnabled(true);

        menu->exec(cur.pos());
        menu->show();


}

void NewTable::copy(){
    ctutor->clear();
    cproblem->clear();
    cassist->clear();
    cmail->clear();

    int cid=((Table)(table->at(pos[i][j]))).getId();
    int k=0,c=assist->count(),kk=0;
    while(kk<c){
        if(((Assist)(assist->at(k))).getCid()==cid){
            int v=0,d=tutor->count(),vv=0;

            while(vv<d){

                if(((Tutor)(tutor->at(v))).getId()==((Assist)(assist->at(k))).getTid()){
                     ctutor->append(((Tutor)(tutor->at(v))));
                     int u=0,uu=0,f=mail->count();
                     while(uu<f){
                         if(((Email)(mail->at(u))).getId()==((Tutor)(tutor->at(v))).getId()){
                             cmail->append(((Email)(mail->at(u))));

                         }
                         uu++;
                         u++;
                     }


                }
                vv++;
                v++;
            }

        }
        kk++;
        k++;
    }
   k=0;
   kk=0;
   c=problem->count();
    while(kk<c){
        if(((Problem)(problem->at(k))).getId()==cid){
            cproblem->append(((Problem)(problem->at(k))));
        }
        k++;
        kk++;


}
    ctable=new Table(((Table)(table->at(pos[i][j]))).getClassname(),((Table)(table->at(pos[i][j]))).getTeacher(),((Table)(table->at(pos[i][j]))).getWeek(),
                     ((Table)(table->at(pos[i][j]))).getTime(),((Table)(table->at(pos[i][j]))).getClassroom(),((Table)(table->at(pos[i][j]))).getType());

copyok=true;
}
void NewTable::paste(){
    if(i!=ctable->getTime()||j!=ctable->getWeek()){


        if(pos[i][j]!=-1){
            int cid=((Table)(table->at(pos[i][j]))).getId();
            int k=0,c=assist->count(),kk=0;
            while(kk<c){
                if(((Assist)(assist->at(k))).getCid()==cid){
                    int v=0,d=tutor->count(),vv=0;

                    while(vv<d){

                        if(((Tutor)(tutor->at(v))).getId()==((Assist)(assist->at(k))).getTid()){

                             int u=0,uu=0,f=mail->count();
                             while(uu<f){
                                 if(((Email)(mail->at(u))).getId()==((Tutor)(tutor->at(v))).getId()){

                                     mail->removeAt(u);
                                     u--;
                                 }
                                 uu++;
                                 u++;
                             }
                             tutor->removeAt(v);
                             v--;

                        }
                        vv++;
                        v++;
                    }
                    assist->removeAt(k);
                    k--;

                }
                kk++;
                k++;
            }
           k=0;
           kk=0;
           c=problem->count();
            while(kk<c){
                if(((Problem)(problem->at(k))).getId()==cid){

                    problem->removeAt(k);
                    k--;
                }
                k++;
                kk++;

            }

        }
    ctable->setId(table->count());
    Table t(ctable->getClassname(),ctable->getTeacher(),j,i,ctable->getClassroom(),ctable->getType());
    t.setId(table->count());
    table->append(t);

    for(int k=0;k<ctutor->count();k++) {
        Tutor tr(tutor->count(),((Tutor)(ctutor->at(k))).getTel(),((Tutor)(ctutor->at(k))).getName());
        tutor->append(tr);
        Assist a(t.getId(),tr.getId());
        assist->append(a);
        for(int kk=0;kk<cmail->count();kk++) {
            if(((Email)(cmail->at(kk))).getId()==((Tutor)(ctutor->at(k))).getId()){
                Email em(tr.getId(),((Email)(cmail->at(kk))).getAdd());
            mail->append(em);
            }
        }

    }

    for(int k=0;k<cproblem->count();k++) {

        Problem p(t.getId(),((Problem)(cproblem->at(k))).getTitle(),((Problem)(cproblem->at(k))).getType(),
                  ((Problem)(cproblem->at(k))).getTexe(),((Problem)(cproblem->at(k))).getDdl(),((Problem)(cproblem->at(k))).getMail());
        problem->append(p);
    }
    pos[i][j]=table->count()-1;
     ui->tableWidget->setItem(i,j,new QTableWidgetItem(t.getClassname()+"("+t.getClassroom()+") "+t.getTeacher()));
}


}

void NewTable::getxy(int row,int column){
    if(row>=0&&column>=0){
   // i=row;
    //j=column;
      int k=pos[row][column];

      QString str="",str1="";
      if(k<table->count()&&k>=0){

     for(int i=0;i<assist->count();i++){

         if(((Assist)(assist->at(i))).getCid()==((Table)(table->at(k))).getId()){
             if(str=="")str="Tutor:\n";
            int tr=((Assist)(assist->at(i))).getTid();
            str=str+((Tutor)(tutor->at(tr))).getName();
            if(((Tutor)(tutor->at(tr))).getTel()!=NULL){


                str=str+" tel:"+((Tutor)(tutor->at(tr))).getTel()+"\n";
            }
         }

     }


     for(int i=0;i<problem->count();i++){

         if(((Problem)(problem->at(i))).getId()==((Table)(table->at(k))).getId()){
             if(str1=="") str1=str1+"Problem:\n";
             QString type;
             switch (((Problem)(problem->at(i))).getType()) {
             case 0:type="Finally Test";

                 break;
             case 1:type="Midlle Test";

                 break;
             case 2:type="Other Test";

                 break;

             }


            str1=str1+((Problem)(problem->at(i))).getTitle()+":"+type+" ddl:"+((Problem)(problem->at(i))).getDdl()+"\n";
         }

     }
      }
       ui->tableWidget->setToolTip(str+str1);
}
}
void NewTable::on_pushButton_clicked()
{

    if(ui->lineEdit->text()==NULL){
        QMessageBox::information(NULL, "!!!", "table name is null",0 ,0);
      }
    else{
     QSqlQuery query,q2,q3,q4,q5;
      query.exec("seletc count(id) from subject");
      int k=query.value(0).toInt();
      query.prepare("insert into subject values (?,?,?,?,?,?,?,?)");
      for(int i=0;i<table->count();i++){
      query.bindValue(0,k);
      query.bindValue(1,((Table)(table->at(i))).getClassname());
      query.bindValue(2,((Table)(table->at(i))).getTeacher());
      query.bindValue(3,((Table)(table->at(i))).getWeek());
      query.bindValue(4,((Table)(table->at(i))).getTime());
      query.bindValue(5,ui->lineEdit->text());
      query.bindValue(6,((Table)(table->at(i))).getClassroom());
      query.bindValue(7,((Table)(table->at(i))).getType());

      query.exec();
      for(int ii=0;ii<problem->count();ii++){

          if(((Problem)(problem->at(ii))).getId()==((Table)(table->at(i))).getId()){

              q2.prepare("insert into problem (class_id int,title string,type int,text string,ttime string,mail string)");
              q2.bindValue(0,k);
              q2.bindValue(1,((Problem)(problem->at(ii))).getTitle());
              q2.bindValue(2,((Problem)(problem->at(ii))).getType());
              q2.bindValue(3,((Problem)(problem->at(ii))).getTexe());
              q2.bindValue(4,((Problem)(problem->at(ii))).getDdl());
              q2.bindValue(5,((Problem)(problem->at(ii))).getMail());
              q2.exec();

          }


      }



      for(int ii=0;ii<assist->count();ii++){
            q3.exec("seletc count(id) from tutor");
            int trk=query.value(0).toInt();

               if(((Assist)(assist->at(ii))).getCid()==((Table)(table->at(i))).getId()){

                  int tr=((Assist)(assist->at(ii))).getTid();
                  ((Tutor)(tutor->at(tr))).getTel();

                   q3.prepare("insert into tutor values(?,?,?)");
                   q3.bindValue(0,trk);
                   q3.bindValue(1,((Tutor)(tutor->at(tr))).getName());
                   q3.bindValue(2,((Tutor)(tutor->at(tr))).getTel());
                   q3.exec();
                   q4.prepare("insert into assist values(?,?)");
                   q4.bindValue(0,k);
                   q4.bindValue(1,trk);
                   q4.exec();
                   for(int j=0;j<mail->count();j++){
                       if(((Email)(mail->at(j))).getId()==((Tutor)(tutor->at(tr))).getId()){

                           q5.prepare("insert into mail (?,?)");
                           q5.bindValue(0,trk);
                           q5.bindValue(1,((Email)(mail->at(j))).getAdd());
                           q5.exec();
                       }


               }

                   trk++;
               }

        }
        k++;
      }
      emit sendt(ui->lineEdit->text());
      this->hide();
}
}
void NewTable::ini_table(){

ui->tableWidget->setRowCount(11);
ui->tableWidget->setColumnCount(7);
QStringList header;
header<<"Monday"<<"Tuesday"<<"Wednesday"<<"Thursday"<<"Friday"<<"Saturday"<<"Sunday";
ui-> tableWidget->setHorizontalHeaderLabels(header);
resize(600,400);

}
void NewTable::on_pushButton_2_clicked()
{
    if(pos[i][j]==-1){
    NewClass *nc =new NewClass(this);
    connect(this,SIGNAL(sendxy(int,int,int)),nc,SLOT(receivexy(int,int,int)));
    connect(nc,SIGNAL(sendtable(Table,QList<Tutor>*,QList<Problem>*,QList<Email>*)),this,SLOT(rec_table(Table,QList<Tutor>*,QList<Problem>*,QList<Email>*)));
    count=tutor->count();
    emit sendxy(i,j,count);
    nc->show();
    }else{
        QList<Tutor>* t=new QList<Tutor>();
        QList<Problem>* p=new QList<Problem>();
        QList<Email>* e=new QList<Email>();
        int cid=((Table)(table->at(pos[i][j]))).getId();
        int k=0,c=assist->count(),kk=0;
        while(kk<c){
            if(((Assist)(assist->at(k))).getCid()==cid){
                int v=0,d=tutor->count(),vv=0;

                while(vv<d){

                    if(((Tutor)(tutor->at(v))).getId()==((Assist)(assist->at(k))).getTid()){
                         t->append(((Tutor)(tutor->at(v))));
                         int u=0,uu=0,f=mail->count();
                         while(uu<f){
                             if(((Email)(mail->at(u))).getId()==((Tutor)(tutor->at(v))).getId()){
                                 e->append(((Email)(mail->at(u))));
                                 mail->removeAt(u);
                                 u--;
                             }
                             uu++;
                             u++;
                         }
                         tutor->removeAt(v);
                         v--;

                    }
                    vv++;
                    v++;
                }
                assist->removeAt(k);
                k--;

            }
            kk++;
            k++;
        }
       k=0;
       kk=0;
       c=problem->count();
        while(kk<c){
            if(((Problem)(problem->at(k))).getId()==cid){
                p->append(((Problem)(problem->at(k))));
                problem->removeAt(k);
                k--;
            }
            k++;
            kk++;

        }
        NewClass *nc =new NewClass(this);
        connect(this,SIGNAL(send_tpe(Table,QList<Tutor>*,QList<Problem>*,QList<Email>*)),nc,SLOT(rec_tpe(Table,QList<Tutor>*,QList<Problem>*,QList<Email>*)));
        connect(nc,SIGNAL(sendtable(Table,QList<Tutor>*,QList<Problem>*,QList<Email>*)),this,SLOT(rec_table(Table,QList<Tutor>*,QList<Problem>*,QList<Email>*)));

        emit send_tpe((Table)(table->at(pos[i][j])),t,p,e);
        table->removeAt(pos[i][j]);
        nc->show();

    }
}

void NewTable::rec_table(Table t,QList<Tutor> *lt,QList<Problem> *lp,QList<Email>*le){
    t.setId(table->count());
    table->append(t);

    for(int k=0;k<lt->count();k++) {
        tutor->append(((Tutor)(lt->at(k))));
        Assist a(t.getId(),((Tutor)(lt->at(k))).getId());
        assist->append(a);

    }
    for(int k=0;k<le->count();k++) mail->append(((Email)(le->at(k))));
    for(int k=0;k<lp->count();k++) {

        Problem p(t.getId(),((Problem)(lp->at(k))).getTitle(),((Problem)(lp->at(k))).getType(),((Problem)(lp->at(k))).getTexe(),((Problem)(lp->at(k))).getDdl(),((Problem)(lp->at(k))).getMail());
        problem->append(p);
    }
    pos[i][j]=table->count()-1;
     ui->tableWidget->setItem(i,j,new QTableWidgetItem(t.getClassname()+"("+t.getClassroom()+") "+t.getTeacher()));

}

void NewTable::on_tableWidget_cellClicked(int row, int column)
{
    i=row;
    j=column;
}

void NewTable::on_pushButton_3_clicked()
{
    int k=pos[this->i][this->j];
    if(k<table->count()&&k>=0){
    QMessageBox::StandardButton rb = QMessageBox::question(NULL, "!!", "Are you sure to delete?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(rb == QMessageBox::Yes)
    {


       for(int i=0;i<assist->count();i++){

           if(((Assist)(assist->at(i))).getCid()==((Table)(table->at(k))).getId()){

               int tr=((Assist)(assist->at(i))).getTid();
               for(j=0;j<mail->count();j++){
                    if(((Email)(mail->at(j))).getId()==((Tutor)(tutor->at(tr))).getId()){
                        mail->removeAt(j);
                    }

               }
               tutor->removeAt(tr);
                assist->removeAt(i);
              }
           }
       for(int i=0;i<problem->count();i++){

           if(((Problem)(problem->at(i))).getId()==((Table)(table->at(k))).getId()){
               problem->removeAt(i);
              }

       }


table->removeAt(k);
pos[this->i][this->j]=-1;
 ui->tableWidget->setItem(this->i,this->j,new QTableWidgetItem(""));
}

}else{
        QMessageBox::question(NULL, "!!", "no class",0,0);

    }

}
