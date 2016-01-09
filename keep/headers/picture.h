#ifndef PICTURE
#define PICTURE
#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QSpinBox>
#include <QToolBar>
#include <QToolButton>

#include "showpicture.h"

class Picture : public QMainWindow
{
  Q_OBJECT

public:
  Picture(QWidget *parent = 0);
  ~Picture();

  //创建动作
  void createActions();
  //创建菜单
  void createMenus();
  //创建工具栏
  void createToolBars();
ShowPicture *s;     //显示流
private:

  QActionGroup *actGrp;   //一个action组
 QAction *NewPaintAction;
  //文字工具栏，实现对文字的编辑功能 择
  QToolButton *PaintBtn;   //Paint
  //添加一个存放这些字体处理工具的工具栏
  QToolBar *fontToolBar;

  //各项菜单栏
  QMenu *fileMenu;
  QMenu *zoomMenu;
  QMenu *rotateMenu;
  QMenu *mirrorMenu;

  QImage img;   //图片
  QString fileName;     //文件名


  //文件菜单项
   QAction *openPictureAction;

QAction *exitAction;
QAction *SaveFileAction;
QAction *SaveAsFileAction;
  //编辑菜单项
  QAction *cutAction;
  QAction *aboutAction;
  QAction *zoomInAction;
  QAction *zoomOutAction;

  //旋转菜单项
  QAction *rotate90Action;
  QAction *rotate180Action;

  //镜像菜单项
  QAction *mirrorVerticalAction;
  QAction *mirrorHorizontalAction;




  //工具栏
  QToolBar *fileTool;
  QToolBar *zoomTool;
  QToolBar *rotateTool;
  QToolBar *mirrorTool;
  QToolBar *doToolBar;


protected slots:    //添加函数槽
   //-------------------------------------------------------------------------------
   void OpenPicture();    //打开文件
  void ShowZoomIn();    //关于图片的缩放功能
  void ShowZoomOut();   //图片缩小
  void ShowRotate90();    //旋转90度
  void ShowRotate180();   //180度
  void ShowMirrorVertical();    //水平镜像
  void ShowMirrorHorizontal();    //垂直镜像
  //-------------------------------------------------------------------------------
  //添加文字处理的相应槽函数
  //当光标所在的字符格式改变的时候，调用这个函数，这个函数根据新的格式将工具栏上的控件显示更新

};


#endif // PICTURE

