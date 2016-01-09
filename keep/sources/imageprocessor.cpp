#include "keep/headers/imageprocessor.h"
#include "keep/headers/paintpanelmainwindow.h"
#include "keep/headers/picture.h"
#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QColorDialog>
#include <QColor>
#include <QTextList>
#include<QMessageBox>
#include <QtCore>
ImageProcessor::ImageProcessor(QWidget *parent)
  : QMainWindow(parent)
{
  //首先设定标题
  setWindowTitle(tr("Text"));
  flag=0;
  //创建放图像的label和文本输入的地方,把这个设置为中心部件
  showWidget = new ShowWidget(this);    //创建一个对象
  setCentralWidget(showWidget);   //把这个设置为中心

//  qDebug()<<"11111111111111";
  //创建有关字体的部件
  //在工具栏上嵌入控件
  //设置字体
  fontLabel1 = new QLabel(tr("font:"));   //字体标签
  fontComboBox = new QFontComboBox;   //字体选项下拉
  fontComboBox->setFontFilters(QFontComboBox::ScalableFonts);   //显示所有的可缩放的字体
  fontLabel3 = new QLabel(tr("remind:"));   //字号

  remindComboBox = new QComboBox;   //字体选项下拉
  delay=new QTimer(this);

  remindComboBox = new QComboBox;   //字体选项下拉
  remindComboBox->addItem(QWidget:: tr("no remind"));
  remindComboBox->addItem(QWidget:: tr("after 1 min"));
  remindComboBox->addItem(QWidget:: tr("after 5 min"));
  remindComboBox->addItem(QWidget:: tr("after 30 min"));
  remindComboBox->addItem(QWidget:: tr("after 1 h"));
  //字号
  fontLabel2 = new QLabel(tr("size:"));   //字号
  sizeComboBox = new QComboBox;
  QFontDatabase db;   //实现在字号下拉列表框中填充各种不同的字号条目，这个类用于表示当前系统中所有可用的格式信息
  foreach(int size, db.standardSizes())   //第二个参数返回可用标准字号的列表
    {
      sizeComboBox->addItem(QString::number(size)); //QString::number(int size, int base)第二个参数表示这个返回base进制的数
    }

  //粗体
  boldBtn = new QToolButton;
  boldBtn->setIcon(QIcon(":/myImages/Bold.png"));
  boldBtn->setCheckable(true);    //默认选择

  //斜体
  italicBtn = new QToolButton;
  italicBtn->setIcon(QIcon(":/myImages/Italic.jpg"));
  italicBtn->setCheckable(true);

  //下划线
  underlineBtn = new QToolButton;
  underlineBtn->setIcon(QIcon(":/myImages/underline.png"));
  underlineBtn->setCheckable(true);


  //颜色
  colorBtn = new QToolButton;
  colorBtn->setIcon(QIcon(":/myImages/color.png"));
  colorBtn->setCheckable(true);


  createActions();      //创建动作
//  qDebug()<<"222222222222222222";
  createMenus();    //创建菜单
//  qDebug()<<"3333333333333333";
  createToolBars();   //工具

//  qDebug()<<"......";
  //相应的槽函数的连接
  connect(fontComboBox, SIGNAL(activated(QString)), this, SLOT(ShowFontComboBox(QString)));
  connect(remindComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(Remind()));
  connect(sizeComboBox, SIGNAL(activated(QString)), this, SLOT(ShowSizeSpinBox(QString)));
  connect(boldBtn, SIGNAL(clicked()), this, SLOT(ShowBoldBtn()));
  connect(italicBtn, SIGNAL(clicked()), this, SLOT(ShowItalicBtn()));
  connect(underlineBtn, SIGNAL(clicked()), this, SLOT(ShowUnderlineBtn()));

  connect(showWidget->text, SIGNAL(currentCharFormatChanged(QTextCharFormat)), this, SLOT(ShowCurrentFormatChanged(QTextCharFormat&)));

  connect(showWidget->text, SIGNAL(cursorPositionChanged()), this, SLOT(ShowCursorPositionChanged()));

}


//实现段落的对齐
void ImageProcessor::ShowAlignment(QAction *act)
{
  if(act == leftAction)
    showWidget->text->setAlignment(Qt::AlignLeft);    //接受到相应的信号应用到文本上
  if(act == rightAction)
    showWidget->text->setAlignment(Qt::AlignRight);
  if(act == centerAction)
    showWidget->text->setAlignment(Qt::AlignCenter);
  if(act == justifyAction)
    showWidget->text->setAlignment(Qt::AlignJustify);
}


//把对应的状态显示在工具栏上
void ImageProcessor::ShowCursorPositionChanged()
{
  if(showWidget->text->alignment() == Qt::AlignLeft)
    leftAction->setChecked(true);   //改变为选中状态
  if(showWidget->text->alignment() == Qt::AlignRight)
    rightAction->setChecked(true);
  if(showWidget->text->alignment() == Qt::AlignCenter)
    centerAction->setChecked(true);
  if(showWidget->text->alignment() == Qt::AlignJustify)
    justifyAction->setChecked(true);
}
//工具栏的实现
void ImageProcessor::createToolBars()
{

  //文件工具条
  fileTool = addToolBar("File");
  fileTool->addAction(openFileAction);
   fileTool->addAction(openPictureAction);
  fileTool->addAction(cutAction);
  fileTool->addAction(NewFileAction);
  fileTool->addAction(SaveAsFileAction);
fileTool->addAction(MemoAction);
fileTool->addAction(saveMemoAction);
 fileTool->addWidget(fontLabel3);   //remind
fileTool->addWidget(remindComboBox);
  //文字的工具栏

//文件工具条
  fontToolBar = addToolBar("Font");
  fontToolBar->addWidget(fontLabel1);   //字体
  fontToolBar->addWidget(fontComboBox);     //字体下拉框
  fontToolBar->addWidget(fontLabel2);   //字号
  fontToolBar->addWidget(sizeComboBox);   //字号下拉
  fontToolBar->addSeparator();    //分割线
  fontToolBar->addWidget(boldBtn);    //加粗
  fontToolBar->addWidget(italicBtn);    //斜
  fontToolBar->addWidget(underlineBtn);   //下划线
  fontToolBar->addSeparator();
  fontToolBar->addWidget(colorBtn);   //颜色

  fileTool->setAllowedAreas(Qt::TopToolBarArea|Qt::LeftToolBarArea);
}

//设置字符格式
//当光标所在的字符格式改变的时候，调用这个函数，这个函数根据新的格式将工具栏上的控件显示更新
void ImageProcessor::ShowCurrentFormatChanged(const QTextCharFormat &fmt)
{
  fontComboBox->setCurrentIndex(fontComboBox->findText(fmt.fontFamily()));
  sizeComboBox->setCurrentIndex(sizeComboBox->findText(QString::number(fmt.fontPointSize())));
  boldBtn->setChecked(fmt.font().bold());
  italicBtn->setChecked(fmt.fontItalic());
  underlineBtn->setChecked(fmt.fontUnderline());
}

//设置颜色
void ImageProcessor::ShowColorBtn()
{
  QColor color = QColorDialog::getColor(Qt::red, this);   //第一个参数指定默认选择的颜色，第二个定义了标准对话框的父窗口

  if(color.isValid())
    {
      QTextCharFormat fmt;
      fmt.setForeground(color);   //设置颜色
      showWidget->text->mergeCurrentCharFormat(fmt);
    }
}
void ImageProcessor::openMemo()
{
    if(flag==1)
    {
        QMessageBox::critical(this,
                              "critical",
                              "Memo Board has been opened"
                              );
    }
    else{
    QString fileName="/root/v2/Memo";
    QFile file(fileName);
   flag=1;
   if(file.open(QIODevice::ReadWrite|QIODevice::Text))
                  {
                    QTextStream textStream(&file);
                    while(!textStream.atEnd())    //循环到后面
                      {
                         showWidget->text->clear();
                        showWidget->text->append(textStream.readLine());    //给文档添加文件
                      }
                    printf("end\n");
              }
   setCurrentFile(fileName);
}
}
void ImageProcessor::saveMemo()
{
    if(flag==0)
    {
        QMessageBox::critical(this,
                              "critical",
                              "You have not open Memo Board"
                              );
    }
    else{
    QString fileName="/root/v2/Memo";
    QFile file(fileName);
    if(file.open(QFile::ReadWrite|QIODevice::Text))
    {
        QTextStream out(&file);
        flag=0;
        out<<showWidget->text->toPlainText();
        QMessageBox::critical(this,
                              "critical",
                              "save successfully"
                              );
        showWidget->text->clear();
    }

}
}
void ImageProcessor::Remind()
{
    remindComboBox->setCurrentText(remindComboBox->currentText());
    int num=remindComboBox->currentIndex();

    if(num==0){
        if(delay->isActive()){
            QMessageBox::StandardButton ret;
            ret = QMessageBox::warning(this,
                                       "warning",
    "You have set a reminder,do you want to cancel it?",                                   QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel
                                       );
            if(ret == QMessageBox::Save){
              delay->stop();
}
        }
    }
   if(num==1){
       if(delay->isActive()){
           QMessageBox::StandardButton ret;
           ret = QMessageBox::warning(this,
                                      "warning",
   "You have set a reminder,do you want to cancel it?",                                   QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel
                                      );
           if(ret == QMessageBox::Save){
             delay->stop();
}
 }
       delay->singleShot(60000,this,SLOT(timerUpDate()));

   }
   if(num==2){
       if(delay->isActive()){
           QMessageBox::StandardButton ret;
           ret = QMessageBox::warning(this,
                                      "warning",
   "You have set a reminder,do you want to cancel it?",                                   QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel
                                      );
           if(ret == QMessageBox::Save){
             delay->stop();
}
  }
    QTimer::singleShot( 300000,this, SLOT(timerUpDate()));

   }
   if(num==3){
       if(delay->isActive()){
           QMessageBox::StandardButton ret;
           ret = QMessageBox::warning(this,
                                      "warning",
   "You have set a reminder,do you want to cancel it?",                                   QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel
                                      );
           if(ret == QMessageBox::Save){
             delay->stop();
}
   }
   QTimer::singleShot(1800000,this, SLOT(timerUpDate()) );
   }
   if(num==4){
       if(delay->isActive()){
           QMessageBox::StandardButton ret;
           ret = QMessageBox::warning(this,
                                      "warning",
   "You have set a reminder,do you want to cancel it?",                                   QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel
                                      );
           if(ret == QMessageBox::Save){
             delay->stop();
}
   }
   QTimer::singleShot(3600000,this, SLOT(timerUpDate()) );
   }
}

//下划线
void ImageProcessor::ShowUnderlineBtn()
{
  QTextCharFormat fmt;
  fmt.setFontUnderline(underlineBtn->isChecked());
  showWidget->text->mergeCurrentCharFormat(fmt);
}

//设置字体倾斜
void ImageProcessor::ShowItalicBtn()
{
  QTextCharFormat fmt;
  fmt.setFontItalic(italicBtn->isChecked());
  showWidget->text->mergeCurrentCharFormat(fmt);
}

//设置文字加粗
void ImageProcessor::ShowBoldBtn()
{
  QTextCharFormat fmt;
  fmt.setFontWeight(boldBtn->isChecked()?QFont::Bold:QFont::Normal);
  showWidget->text->mergeCurrentCharFormat(fmt);    //应用进去
}

//设置字号
void ImageProcessor::ShowSizeSpinBox(QString spinValue)
{
  QTextCharFormat fmt; //文体字符格式
  fmt.setFontPointSize(spinValue.toFloat());    //设置字体大小
  showWidget->text->mergeCurrentCharFormat(fmt);//将新的格式应用到光标选区内的字符
}

//设置字体
void ImageProcessor::ShowFontComboBox(QString comboStr)
{
  QTextCharFormat fmt;    //文体字符格式
  fmt.setFontFamily(comboStr);    //选择的字体名称设置给QTextCharFormat
  mergeFormat(fmt);   //将新的格式应用到光标选区内的字符
}

//通过QTextCursor来对QTextDocument进行修改
void ImageProcessor::mergeFormat(QTextCharFormat format)
{
  QTextCursor cursor = showWidget->text->textCursor();    //得到这个类
  if(!cursor.hasSelection())    //若光标没有高亮选区，则把光标所在的词作为选区，以空格或“，”或“。”等标点符号分割
    cursor.select(QTextCursor::WordUnderCursor);
  cursor.mergeCharFormat(format);   //把格式应用到光标所在的字符上
  showWidget->text->mergeCurrentCharFormat(format);   //调用这个函数将格式应用到选区内的所有字符上

}

//菜单的实现
void ImageProcessor::createMenus()
{
  //文件菜单
  fileMenu = menuBar()->addMenu(tr("file"));
  fileMenu->addAction(openFileAction);
  fileMenu->addAction(openPictureAction);
  fileMenu->addAction(cutAction);
  fileMenu->addAction(NewFileAction);
  fileMenu->addAction(SaveAsFileAction);
  fileMenu->addSeparator(); //分隔符
  fileMenu->addAction(exitAction);
  fileMenu->addAction(MemoAction);
  fileMenu->addAction(saveMemoAction);
}

//动作的实现
void ImageProcessor::createActions()
{
  //排版的各种操作的触发事件
  actGrp = new QActionGroup(this);      //创建一个action组
  leftAction = new QAction(QIcon(":/myImages/left.jpg"), "left", actGrp);    //左对齐的图标
  leftAction->setCheckable(true);   //设定按钮是否可以选定

  rightAction = new QAction(QIcon(":/myImages/right.jpg"), "right", actGrp);   //右对齐
  rightAction->setCheckable(true);

  centerAction = new QAction(QIcon(":/myImages/center.jpg"), "center", actGrp);   //居中对齐
  centerAction->setCheckable(true);

  justifyAction = new QAction(QIcon(":/myImages/justify.jpg"), "justify", actGrp);   //两端对齐
  justifyAction->setCheckable(true);

  connect(actGrp, SIGNAL(triggered(QAction*)), this, SLOT(ShowAlignment(QAction*)));    //接受选择的action然后显示相应的结果


  //打开动作
//  qDebug()<<"11111111111111";
  openFileAction = new QAction(QIcon(":/myImages/open.jpg"), tr("open"), this);    //设置图片，名字
  openFileAction->setStatusTip(tr("open a file"));    //设置提示

  connect(openFileAction, SIGNAL(triggered()), this, SLOT(ShowOpenFile()));

  openPictureAction = new QAction(QIcon(":/myImages/openpic.jpeg"), tr("openpic"), this);    //设置图片，名字
  openPictureAction->setStatusTip(tr("openpic a file"));    //设置提示

  connect(openPictureAction, SIGNAL(triggered()), this, SLOT(ShowOpenPicture()));

  //打开动作
//  qDebug()<<"11111111111111";
  MemoAction = new QAction(QIcon(":/myImages/2.jpg"), tr("open memo"), this);    //设置图片，名字
  MemoAction->setStatusTip(tr("open memo"));    //设置提示

  connect(MemoAction, SIGNAL(triggered()), this, SLOT(openMemo()));
  //打开动作
//  qDebug()<<"11111111111111";
  saveMemoAction = new QAction(QIcon(":/myImages/3.jpg"), tr("save memo"), this);    //设置图片，名字
  saveMemoAction->setStatusTip(tr("save memo"));    //设置提示

  connect(saveMemoAction, SIGNAL(triggered()), this, SLOT(saveMemo()));

  cutAction = new QAction(QIcon(":/myImages/paint.jpg"), tr("Paint"), this);    //设置图片，名字
  cutAction->setStatusTip(tr("Paint"));    //设置提示
  connect(cutAction, SIGNAL(triggered()), this, SLOT(c()));
  //新建动作
  NewFileAction = new QAction(QIcon(":/myImages/new.png"), tr("new"), this);    //设置图片，名字
  NewFileAction->setStatusTip(tr("new a file"));    //设置提示
  connect(NewFileAction, SIGNAL(triggered()), this, SLOT(ShowNewFile()));   //连接上相应的槽

  //save
  SaveFileAction = new QAction(QIcon(":/myImages/Save.png"), tr("save"), this);    //设置图片，名字
  SaveFileAction->setStatusTip(tr("save a file"));    //设置提示
  connect(SaveFileAction, SIGNAL(triggered()), this, SLOT(slotSave()));   //连接上相应的槽

  //saveas
  SaveAsFileAction = new QAction(QIcon(":/myImages/SaveAs.png"), tr("save"), this);    //设置图片，名字
  SaveAsFileAction->setStatusTip(tr("save a file"));    //设置提示
  connect(SaveAsFileAction, SIGNAL(triggered()), this, SLOT(slotSaveAs()));   //连接上相应的槽
  //退出动作
  exitAction = new QAction(tr("out"), this);    //设置图片，名字
  exitAction->setStatusTip(tr("close"));    //设置提示
  connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));


  cutAction = new QAction(QIcon(":/myImages/paint.jpg"), tr("Paint"), this);    //设置图片，名字
  cutAction->setStatusTip(tr("Paint"));    //设置提示
  connect(cutAction, SIGNAL(triggered()), this, SLOT(c()));


}


//打开文件
void ImageProcessor::ShowOpenFile()
{
    if(flag==1)
    {
        QMessageBox::critical(this,
                              "critical",
                              "Save Memo Board?"
                              );
   saveMemo();
    }
    else{
  fileName = QFileDialog::getOpenFileName(this);    //得到文件名
  if(!fileName.isEmpty())   //文件不为空
    {
      if(showWidget->text->document()->isEmpty()) //中心部件的内容的根节点不是空
        {
          loadFile(fileName);   //添加文件
        }
      else
        {
          ImageProcessor *newImageProcessor = new ImageProcessor;   //创建一个新的my word文档

          newImageProcessor->setFixedSize(800, 500);
          newImageProcessor->move(300,30);
           newImageProcessor->show();    //显示出来
          newImageProcessor->loadFile(fileName);    //添加文件
        }
    }
}
}
//打开文件
void ImageProcessor::ShowOpenPicture()
{
    Picture *picture = new Picture;   //创建一个新的my word文档
    picture->show();    //显示出来
}
//实现loadFile函数,这个文件的处理后面会再次进行学习
void ImageProcessor::loadFile(QString filename)
{
  printf("file name:%s\n", filename.data());    //输出文件名

  QFile file(filename);
  if(file.open(QIODevice::ReadOnly|QIODevice::Text|QFile::Truncate))
    {
      QTextStream textStream(&file);
      while(!textStream.atEnd())    //循环到后面
        {
          showWidget->text->append(textStream.readLine());    //给文档添加文件
          printf("read line\n");
        }
      printf("end\n");
    }

}

//新建文件槽
void ImageProcessor::ShowNewFile()
{
    if(maybeSave())
        {
            showWidget->text->clear();
            setCurrentFile("");
        }

}

void ImageProcessor::c()
{

    PaintPanelMainWindow *p=new PaintPanelMainWindow();
    p->show();

}
bool ImageProcessor::maybeSave()
{
    if(showWidget->text->document()->isModified())
    {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this,
                                   "warning",
"the document has been modified,Do you want to save your change",                                   QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel
                                   );
        if(ret == QMessageBox::Save)
            return slotSave();
        if(ret == QMessageBox::Cancel)
            return false;
    }
    else
        return true;
}
void ImageProcessor::setCurrentFile(const QString &fileName)
{

    showWidget->text->document()->setModified(false);
    this->setWindowModified(false);
    fileName.isEmpty() ?
                this->setWindowFilePath("Untitle.txt"):
                this->setWindowFilePath(fileName);
}

bool ImageProcessor::slotSaveAs()
{
    QString fileName =QFileDialog::getSaveFileName(this);
    if(fileName.isEmpty())
        return false;
    else
        return saveFile(fileName);
}
bool ImageProcessor::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly|QFile::Text))
    {
        QMessageBox::critical(this,
                              "critical",
                              "cannot write file"
                              );
        return false;
    }
    else
    {
        QTextStream out(&file);
        out<<showWidget->text->toPlainText();
        setCurrentFile(fileName);
        return true;
    }
}
bool ImageProcessor::slotSave()
{
    if(fileName.isEmpty())
        return slotSaveAs();
    else
        return saveFile(fileName);
}
void ImageProcessor::timerUpDate()

{
        QMessageBox::critical(this,
                              "critical",
                              "It is to check Memo Board ^_^"
                              );
remindComboBox->setCurrentText("no remind");
}
ImageProcessor::~ImageProcessor()
{

}
