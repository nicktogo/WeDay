#include "keep/headers/picture.h"
#include "keep/headers/paintpanelmainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QColorDialog>
#include <QColor>
#include <QTextList>
#include<QMessageBox>
Picture::Picture(QWidget *parent)
  : QMainWindow(parent)
{
  //首先设定标题
  setWindowTitle(tr("Picture"));

  //创建放图像的label把这个设置为中心部件
  s = new ShowPicture(this);    //创建一个对象
  setCentralWidget(s);   //把这个设置为中心

  createActions();      //创建动作
//  qDebug()<<"222222222222222222";
  createMenus();    //创建菜单
//  qDebug()<<"3333333333333333";
  createToolBars();   //工具

}



//工具栏的实现
void Picture::createToolBars()
{

  //文件工具条
  fileTool = addToolBar("File");
   fileTool->addAction(openPictureAction);
  //编辑工具条
  zoomTool = addToolBar("Edit");
//  zoomTool->addAction(aboutAction);
  zoomTool->addSeparator(); //分隔符
  zoomTool->addAction(zoomInAction);
  zoomTool->addAction(zoomOutAction);

  //旋转工具
  rotateTool = addToolBar("rotate");
  rotateTool->addAction(rotate90Action);
  rotateTool->addAction(rotate180Action);

  mirrorTool=addToolBar("mirror");
mirrorTool->addAction(mirrorVerticalAction);
mirrorTool->addAction(mirrorHorizontalAction);
}





//菜单的实现
void Picture::createMenus()
{
  //文件菜单
  fileMenu = menuBar()->addMenu(tr("file"));
  fileMenu->addAction(openPictureAction);
  fileMenu->addSeparator(); //分隔符
  fileMenu->addAction(exitAction);

  //缩放菜单
  zoomMenu = menuBar()->addMenu(tr("zoom"));  //缩放
  zoomMenu->addSeparator(); //分隔符
  zoomMenu->addAction(zoomInAction);
  zoomMenu->addAction(zoomOutAction);

  //旋转菜单
  rotateMenu = menuBar()->addMenu(tr("rotate"));
  rotateMenu->addAction(rotate90Action);
  rotateMenu->addAction(rotate180Action);

  //镜像菜单
  mirrorMenu = menuBar()->addMenu(tr("mirror"));
  mirrorMenu->addAction(mirrorVerticalAction);
  mirrorMenu->addAction(mirrorHorizontalAction);


}

//动作的实现
void Picture::createActions()
{
  openPictureAction = new QAction(QIcon(":/myImages/openpic.jpeg"), tr("openpic"), this);    //设置图片，名字
  openPictureAction->setStatusTip(tr("openpic a file"));    //设置提示

  connect(openPictureAction, SIGNAL(triggered()), this, SLOT(OpenPicture()));

  //退出动作
  exitAction = new QAction(tr("out"), this);    //设置图片，名字
  exitAction->setStatusTip(tr("close"));    //设置提示
  connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));


  //放大图像
  zoomInAction = new QAction(QIcon(":/myImages/zoomin.png"), tr("get big"), this);
  zoomInAction->setStatusTip(tr("get big image"));
  connect(zoomInAction, SIGNAL(triggered()), this, SLOT(ShowZoomIn())); //进行图片放大

  //缩小
  zoomOutAction = new QAction(QIcon(":/myImages/zoomout.png"), tr("get small"), this);
  zoomOutAction->setStatusTip(tr("get small image"));
  connect(zoomOutAction, SIGNAL(triggered()), this, SLOT(ShowZoomOut())); //进行图片放小


  //实现图片的选择动作
  //旋转90°
  rotate90Action = new QAction(QIcon(":/myImages/rotate270.jpg"), tr("get rotate90"), this);
  rotate90Action->setStatusTip(tr("get rotate90 image"));
  connect(rotate90Action, SIGNAL(triggered()), this, SLOT(ShowRotate90()));
  //180°
  rotate180Action = new QAction(QIcon(":/myImages/rotate180.jpg"), tr("get rotate180"), this);
  rotate180Action->setStatusTip(tr("get rotate180 image"));
  connect(rotate180Action, SIGNAL(triggered()), this, SLOT(ShowRotate180()));



  //实现图像镜像的动作
  //纵向
  mirrorVerticalAction = new QAction(QIcon(":/myImages/mirrorVertical.png"), tr("mirrorVertical"), this);
  mirrorVerticalAction->setStatusTip(tr("mirrorVertical the image"));
  connect(mirrorVerticalAction, SIGNAL(triggered()), this, SLOT(ShowMirrorVertical()));
  //横向
  mirrorHorizontalAction = new QAction(QIcon(":/myImages/mirrorHorizontal.png"), tr("mirrorHorizontal"), this);
  mirrorHorizontalAction->setStatusTip(tr("mirrorHorizontal the image"));
  connect(mirrorHorizontalAction, SIGNAL(triggered()), this, SLOT(ShowMirrorHorizontal()));

}


//水平镜像
void Picture::ShowMirrorHorizontal()
{
  if(img.isNull())
    return;
  img = img.mirrored(true, false);    //水平镜像
  s->imageLabel->setPixmap(QPixmap::fromImage(img));

}

//垂直镜像
void Picture::ShowMirrorVertical()
{
  if(img.isNull())
    return;
  img = img.mirrored(false, true);    //垂直镜像
  s->imageLabel->setPixmap(QPixmap::fromImage(img));
}



//旋转180度
void Picture::ShowRotate180()
{
  if(img.isNull())
    return;
  QMatrix matrix;
  matrix.rotate(180);    //旋转180度
  img = img.transformed(matrix);    //图像旋转之后再重新得到赋值
  s->imageLabel->setPixmap(QPixmap::fromImage(img));
}

//旋转90度
void Picture::ShowRotate90()
{
  if(img.isNull())
    return;
  QMatrix matrix;
  matrix.rotate(90);    //旋转90度
  img = img.transformed(matrix);    //图像旋转之后再重新得到赋值
  s->imageLabel->setPixmap(QPixmap::fromImage(img));
}

//实现图片的放小
void Picture::ShowZoomOut()
{
  //首先判断是否有照片
  if(img.isNull())
    return;   //没有照片，那就不用放大了
  QMatrix martix;   //一个图片的存放对象
  martix.scale(0.5, 0.5);   //长和宽都放小2倍
  img = img.transformed(martix);    //对图片的操作落实
  s->imageLabel->clear();
  s->imageLabel->setPixmap(QPixmap::fromImage(img));   //改变后的图片放回去

}

//实现图片的放大
void Picture::ShowZoomIn()
{
  //首先判断是否有照片
  if(img.isNull())
    return;   //没有照片，那就不用放大了
  QMatrix martix;   //一个图片的存放对象
  martix.scale(2, 2);   //长和宽都放大2倍
  img = img.transformed(martix);    //对图片的操作落实
  s->imageLabel->setPixmap(QPixmap::fromImage(img));   //改变后的图片放回去

}
void Picture::OpenPicture()
{
    fileName = QFileDialog::getOpenFileName(this);    //得到文件名

  if(!fileName.isEmpty())   //文件不为空
    {
      fileName=fileName;
       img.load(fileName);
       s->imageLabel->setPixmap(QPixmap::fromImage(img));
      }

}
Picture::~Picture()
{

}
