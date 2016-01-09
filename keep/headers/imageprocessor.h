#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QComboBox>
#include <QSpinBox>
#include <QToolBar>
#include <QFontComboBox>
#include <QToolButton>
#include <QTextCharFormat>
#include<QTimer>
#include "showwidget.h"

class ImageProcessor : public QMainWindow
{
  Q_OBJECT

public:
  ImageProcessor(QWidget *parent = 0);
  ~ImageProcessor();

  //创建动作
  void createActions();
  //创建菜单
  void createMenus();
  //创建工具栏
  void createToolBars();
    QTimer *delay;
  int flag=0;
  void loadFile(QString filename);    //加载文件
  void mergeFormat(QTextCharFormat);    //文本格式

private:

  QActionGroup *actGrp;   //一个action组
  QAction *leftAction;    //左对齐
  QAction *rightAction;   //右对齐
  QAction *centerAction;    //居中对齐
  QAction *justifyAction;     //两端对齐
 QAction *NewPaintAction;
  //文字工具栏，实现对文字的编辑功能
  QLabel *fontLabel1;   //标签，字体
  QFontComboBox *fontComboBox;    //字体的选择下拉
  QLabel *remind;   //标签，字体
  QComboBox *remindComboBox;    //字体的选择下拉
  QLabel *fontLabel2;   //字号
  QLabel *fontLabel3;   //remind
  QComboBox *sizeComboBox;    //字号下拉
  QToolButton *boldBtn;   //加粗
  QToolButton *italicBtn;   //斜体
  QToolButton *underlineBtn;    //下划线
  QToolButton *colorBtn;    //字体颜色选择
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
  ShowWidget *showWidget;     //显示流

  //文件菜单项
  QAction *openFileAction;
   QAction *openPictureAction;
  QAction *NewFileAction;
   QAction*MemoAction;
   QAction*saveMemoAction;
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
  void ShowCursorPositionChanged();   //光标位置改变？？？
void timerUpDate();
   //-------------------------------------------------------------------------------
  void ShowNewFile();   //新建一个新的文件
  void ShowOpenFile();    //打开文件
   void ShowOpenPicture();    //打开文件
  bool maybeSave();//判断当前文本是否保存
  void setCurrentFile(const QString &);//设置当前文本的文件名
  bool saveFile(const QString &);//保存文本
  void c();
  void ShowAlignment(QAction *act);
    bool slotSave();//保存文本的槽
    bool slotSaveAs();//另存为文本的槽
  //-------------------------------------------------------------------------------
  //添加文字处理的相应槽函数
  void ShowFontComboBox(QString comboStr);    //显示字体的改变
  void ShowSizeSpinBox(QString spinValue);    //字号的改变
  void ShowBoldBtn();   //加粗
  void ShowItalicBtn();   //斜体
  void ShowUnderlineBtn();      //下划线
  void ShowColorBtn();      //颜色的改变
  void ShowCurrentFormatChanged(const QTextCharFormat &fmt);    //设置字符格式
  //当光标所在的字符格式改变的时候，调用这个函数，这个函数根据新的格式将工具栏上的控件显示更新
  void openMemo();
  void saveMemo();
  void Remind();
};

#endif // IMAGEPROCESSOR_H
