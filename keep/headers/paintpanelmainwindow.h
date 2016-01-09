#ifndef PAINTPANELMAINWINDOW_H
#define PAINTPANELMAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QColor>
#include <QPointer>
#include <QMouseEvent>

#include <QMenu>
#include <QMenuBar>
#include <QAction>
namespace Ui {
class PaintPanelMainWindow;
}

class PaintPanelMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PaintPanelMainWindow(QWidget *parent = 0);
    ~PaintPanelMainWindow();
    //创建动作
    void createActions();
    //创建菜单
    void createMenus();
private:
    Ui::PaintPanelMainWindow *ui;
    /** 定义变量 */

    /*** 现在是否是清屏状态 false-->No   true-->Yes*/
    bool isClear;

    /*** 图形的起始坐标和结束坐标 */
    QPoint poi1;
    QPoint poi2;

    /*** 画笔专用花点笔 */
    QPoint poi;
    bool isLineEnd;

    /*** 图形形状  0-->直线 1-->圆形 2-->写字  3-->长方形  */
    qint32 shape;

    /*** 线条颜色 */
    QColor lineColor;

    /*** 线条的粗细 */
    int lineThickness;

    /*** 填充颜色  */
    QColor fillColor;
QMenu *fileMenu;
 QString fileName;     //文件名
 //文件菜单项
 QAction *openFileAction;
  QAction *openPictureAction;
 QAction *NewFileAction;

 QAction *exitAction;
QAction *SaveFileAction;
QAction *SaveAsFileAction;
protected:
    void paintEvent(QPaintEvent *pEvent);
private slots:

    /*** 按下选择线条颜色按钮 */
    void on_lineColorPushButton_clicked();

    /*** 按下选择填充颜色按钮 */
    void on_fillColorPushButton_clicked();

    /*** 鼠标按下 */
    void mousePressEvent(QMouseEvent *mEvent);

    /*** 鼠标移动 */
    void mouseMoveEvent(QMouseEvent *mEvent);

    /*** 鼠标释放 */
    void mouseReleaseEvent(QMouseEvent *mEvent);
    void on_lineSelectSpinBox_valueChanged(const QString &arg1);
    void on_shapSelectComboBox_currentIndexChanged(int index);
    void on_clearPushButton_clicked();
    void on_delPushButton_clicked();


};
#endif // PAINTPANELMAINWINDOW_H
