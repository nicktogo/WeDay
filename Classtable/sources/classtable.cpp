#include "Classtable/headers/classtable.h"
#include "ui_classtable.h"

#include "Classtable/headers/connection.h"
#include "qboxlayout.h"
#include "Classtable/headers/newclass.h"

Classtable::Classtable(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Classtable)
{

    ui->setupUi(this);
    table= new QList<Table>();
    problem=new QList<Problem>();
    tutor=new QList<Tutor>();
    mail=new QList<Email>();
    assist=new QMap<int,int>();
    QWidget *pwidget=new     QWidget(this);
        QHBoxLayout *layout = new QHBoxLayout;
        layout->addWidget(pwidget);


    setWindowTitle(tr("School Timetable"));
    resize(1200,1000);
   if(!createConnection()){
       QMessageBox::critical(0, qApp->tr("Cannot open database"),
           qApp->tr("Unable to establish a database connection."
                    ), QMessageBox::Cancel);
   }

   ui->label_2->setText(" ");
   ui->pushButton->setToolTip("You can look more informatin of tutors,theirs' E-mails and some problems");

   ini_table();
   ini_combx();
}

Classtable::~Classtable()
{
    delete ui;
}

void Classtable::ini_table(){

ui->tableWidget->setRowCount(11);
ui->tableWidget->setColumnCount(7);
QStringList header;
header<<"Monday"<<"Tuesday"<<"Wednesday"<<"Thursday"<<"Friday"<<"Saturday"<<"Sunday";
ui-> tableWidget->setHorizontalHeaderLabels(header);
resize(600,400);
ui->tableWidget->setMouseTracking(true);
connect(ui->tableWidget,SIGNAL( cellEntered(int , int) ),this,SLOT( getxy(int, int) ) );


}
void Classtable::getxy(int row,int column){
    switch(column+1){
    case 1:ui->label_4->setText("Monday");break;
        case 2:ui->label_4->setText("Tuesday");break;
        case 3:ui->label_4->setText("Wednesday");break;
        case 4:ui->label_4->setText("Thursday");break;
        case 5:ui->label_4->setText("Friday");break;
        case 6:ui->label_4->setText("Saturday");break;
        case 7:ui->label_4->setText("Sunday");break;

    }
       ui->label_5->setText("NO."+QString::number(row+1,10));
       ui->tableWidget->setToolTip("xxxx");

}

void Classtable::ini_combx(){
 QSqlQuery query;

// query.exec("insert into subject (id,name,teacher,week,time,tname,classroom,type) values(1,'math','aaa',0,0,'t1','a111','both')");
//query.exec("select * from t");
 //query.exec("insert into mail(id,mail) values(1,'xxxx')");
 //query.exec("select * from mail");
//query.first();
 //qDebug() << query.value(0).toInt();
 query.exec("select tname from subject");
 query.first();
 do{
     qDebug() << query.value(0).toString();
   // QStringList list =QStringList()<<"t1"<<"table1"<<"table2";
    ui->comboBox->addItem(query.value(0).toString());
    ui->comboBox->show();
    //connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onChanged(int)));
}while(query.next());
}

void Classtable::on_tableWidget_cellClicked(int row, int column)
{
    i=row;
    j=column;

    switch(column+1){
    case 1:ui->label_4->setText("Monday");break;
        case 2:ui->label_4->setText("Tuesday");break;
        case 3:ui->label_4->setText("Wednesday");break;
        case 4:ui->label_4->setText("Thursday");break;
        case 5:ui->label_4->setText("Friday");break;
        case 6:ui->label_4->setText("Saturday");break;
        case 7:ui->label_4->setText("Sunday");break;

    }
       ui->label_5->setText("NO."+QString::number(row+1,10));


       //ui->centralWidget->setToolTip("xx");
}




void Classtable::on_pushButton_clicked()
{
    NewClass *nc =new NewClass(this);
    connect(this,SIGNAL(send_type(int,int,int,QString)),nc,SLOT(rec_type(int,int,int,QString)));
   // connect(nc,SIGNAL(sendtable(Table,QList<Tutor>*,QList<Problem>*,QList<Email>*)),this,SLOT(rec_table(Table,QList<Tutor>*,QList<Problem>*,QList<Email>*)));
    //count=tutor->count();
    emit send_type(i,j,1,ui->comboBox->currentText());
    nc->show();

}
void Classtable::cleartable(){
    table->clear();
    problem->clear();
    tutor->clear();
    assist->clear();
    mail->clear();
    for(int i=0;i<11;i++)
        for(int j=0;j<7;j++)
        {
            ui->tableWidget->setItem(i,j,new QTableWidgetItem(" "));
            pos[i][j]=-1;
    }
}


void Classtable::on_pushButton_4_clicked()
{
    cleartable();

    QSqlQuery query;
    QString subname,teacher,tname,classroom,type;
    int week,time,id;
   ui->label_2->setText(ui->comboBox->currentText());
        query.exec("select name,teacher,week,ttime,id,classroom,type from subject where tname='"+ui->comboBox->currentText()+"'");



        while(query.next())
        {


            qDebug() << query.value(0).toString() << query.value(1).toString()<<query.value(2).toInt()<<query.value(3).toInt();
            subname=query.value(0).toString();
            teacher=query.value(1).toString();
            week=query.value(2).toInt();
            time=query.value(3).toInt();
            tname=ui->comboBox->currentText();
            id=query.value(4).toInt();
            classroom=query.value(5).toString();
            type=query.value(6).toString();
            Table newt(id,subname,teacher,week,time,tname);
            table->append(newt);
            pos[time][week]=table->count()-1;

            ui->tableWidget->setItem(time,week,new QTableWidgetItem(subname+"("+classroom+") "+teacher));
            //  ui->label_2->setText(tname);



        }


}

void Classtable::on_pushButton_5_clicked()
{
    NewTable *nt =new NewTable(this);

    connect(nt,SIGNAL(sendt(QString)),this,SLOT(rec_table(QString)));

 //   nt->setWindowFlags(Qt::Dialog|Qt::CustomizeWindowHint);
    nt->show();


}
void Classtable::rec_table(QString name){

ui->comboBox->addItem((name));
ui->comboBox->show();

}

void Classtable::on_pushButton_2_clicked()
{
    NewClass *nc =new NewClass(this);
    connect(this,SIGNAL(send_type(int,int,int,QString)),nc,SLOT(rec_type(int,int,int,QString)));
   // connect(nc,SIGNAL(sendtable(Table,QList<Tutor>*,QList<Problem>*,QList<Email>*)),this,SLOT(rec_table(Table,QList<Tutor>*,QList<Problem>*,QList<Email>*)));
    //count=tutor->count();
    emit send_type(i,j,2,ui->comboBox->currentText());
    nc->show();

}
