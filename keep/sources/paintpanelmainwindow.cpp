#include "keep/headers/paintpanelmainwindow.h"
#include "ui_notepaintpanelmainwindow.h"

#include <QDebug>
#include <QPainter>
#include <QColor>
#include <QColorDialog>
#include <QPalette>
#include <QDateTime>
#include <QVector>
#include <QList>
#include <QPen>
#include <QFileDialog>

/*** 定义存储界面上所有图形的容器 */
QList<PaintPanelMainWindow *> picList;

/*** 定义存储界面上画笔的容器 */
QList<PaintPanelMainWindow *> poiList;

PaintPanelMainWindow::PaintPanelMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PaintPanelMainWindow)
{
    ui->setupUi(this);
    /** 设置随机数的种子,把当前时间的秒作为随机数种子 */
    qsrand(QDateTime::currentDateTime().time().msec());

    /*** 设置线的初始颜色为黑色 */
    lineColor = Qt::black;

    /*** 设置填充的初始颜色为白色 */
    fillColor = QColor(240,240,240);

    /*** 设置画笔的粗细默认为1 */
    ui->lineSelectSpinBox->setValue(1);
    lineThickness = ui->lineSelectSpinBox->value();

    /*** 初始化清屏状态位 */
    isClear = false;

    /*** 在直线的状态下默认，填充颜色按钮不可用 */
    ui->fillColorPushButton->setDisabled(true);

    /*** 画笔的时候判断当前的这条线是否结束 */
    isLineEnd = false;


}

PaintPanelMainWindow::~PaintPanelMainWindow()
{
    delete ui;
}

/** 画图函数 */
void PaintPanelMainWindow::paintEvent(QPaintEvent *pEvent)
{
    /*** 消除警告 */
    pEvent->setAccepted(true);

    /** this是必须有的，说明是在现在的窗口上画的 */
    QPainter painter(this);

    /*** 判断现在是否处于清屏状态 */
    if(false == isClear)
    {
        QPen penNow(lineColor, lineThickness);

        painter.setPen(penNow);

        /*** 先画出当前的那一个 图形的形状*/
        switch(ui->shapSelectComboBox->currentIndex())
        {

            /*** 直线 */
            case 0 :
            {
                 painter.drawLine(poi1.rx(), poi1.ry(),
                             poi2.rx(), poi2.ry());
                 break;
            }
            /*** 圆形 */
            case 1 :
            {
                 /*** 设置图形内部颜色 */
                 painter.setBrush(fillColor);
                 painter.drawEllipse(poi1.rx(), poi1.ry(),
                                         poi2.rx() - poi1.rx(),poi2.ry() - poi1.ry());
                 break;
            }
            /*** 长方形 */
            case 2 :
            {
                 /*** 设置图形内部颜色 */
                 painter.setBrush(fillColor);
                 painter.drawRect(poi1.rx(), poi1.ry(),
                                         poi2.rx() - poi1.rx(),poi2.ry() - poi1.ry());
                 break;
            }
            /*** 自己写字 */
            case 3:
            {
                break;
            }
            default:
            {
                qDebug() << "the linethickness is wrong!";
            }

        }//switch(ui->shapSelectComboBox->currentIndex())

        /*** 如果有画笔画的图形，要把这部分图形要画出来 */

    }
    else
    {
        isClear = false;
    }



    /*** 画出所有的图形  */
    foreach(PaintPanelMainWindow *pTemp,picList)
    {
        /*** step1 得到线的颜色和粗细*/
        QPen pen(pTemp->lineColor,pTemp->lineThickness);
        painter.setPen(pen);

        /*** step3 画图形的形状*/
        switch(pTemp->shape)
        {
            /*** 直线 */
            case 0 :
            {
                 painter.drawLine(pTemp->poi1.rx(), pTemp->poi1.ry(),
                             pTemp->poi2.rx(), pTemp->poi2.ry());
                 break;
            }
            /*** 圆形 */
            case 1 :
            {
                 /*** 设置图形内部颜色 */
                 painter.setBrush(pTemp->fillColor);
                 painter.drawEllipse(pTemp->poi1.rx(), pTemp->poi1.ry(),
                                         pTemp->poi2.rx() - pTemp->poi1.rx(),pTemp->poi2.ry() - pTemp->poi1.ry());
                 break;
            }
            /*** 长方形 */
            case 2 :
            {
                 /*** 设置图形内部颜色 */
                 painter.setBrush(pTemp->fillColor);
                 painter.drawRect(pTemp->poi1.rx(), pTemp->poi1.ry(),
                                         pTemp->poi2.rx() - pTemp->poi1.rx(),pTemp->poi2.ry() - pTemp->poi1.ry());
                 break;
            }
            /*** 自己写字 */
            case 3:
            {
                break;
            }
            default:
            {
                qDebug() << "the linethickness is wrong!";
            }

        }

    }



    for(QList<PaintPanelMainWindow *>::size_type index = 0; index < (poiList.size() - 1); index ++)
    {
        /*** 设置画笔的颜色 */
        QPen penPoi(poiList[index]->lineColor,poiList[index]->lineThickness);
        painter.setPen(penPoi);

        if(false == poiList[index]->isLineEnd)
        {
            painter.drawLine(poiList[index]->poi.rx(), poiList[index]->poi.ry(),
                             poiList[index + 1]->poi.rx(),poiList[index + 1]->poi.ry());
        }

    }


}

/** 选择线条的颜色 */
void PaintPanelMainWindow::on_lineColorPushButton_clicked()
{
    QColor color = QColorDialog::getColor();
    lineColor = color;
    if(color.isValid())
    {
        /** 把颜色在frame上显示出来 */
        QPalette p = ui->lineColorFrame->palette();
        p.setColor(QPalette::Background,color);
        ui->lineColorFrame->setPalette(p);
    }
}


/** 选择封闭图形填充色的颜色 */
void PaintPanelMainWindow::on_fillColorPushButton_clicked()
{
    QColor color = QColorDialog::getColor();
    fillColor = color;
    if(color.isValid())
    {
        /** 把颜色在frame上显示出来 */
        QPalette p = ui->fillColorFrame->palette();
        p.setColor(QPalette::Background,color);
        ui->fillColorFrame->setPalette(p);
    }
}

/*** 鼠标按下 */
void PaintPanelMainWindow::mousePressEvent(QMouseEvent *mEvent)
{
    /*** 如果是画笔状态 */
    if(shape == 3)
    {
        /*** 画笔 */
        poi = mEvent->pos();
        PaintPanelMainWindow *pNew = new PaintPanelMainWindow;
        pNew->poi = poi;
        pNew->isLineEnd = false;
        pNew->lineColor = lineColor;
        pNew->lineThickness = lineThickness;

        poiList << pNew;
    }
    else
    {
        /*** 画图形 */
        poi1 = mEvent->pos();
    }




}

/*** 鼠标移动 */
void PaintPanelMainWindow::mouseMoveEvent(QMouseEvent *mEvent)
{
    /*** 如果是画笔状态 */
    if(shape == 3)
    {
        /*** 画笔 */
        poi = mEvent->pos();
        PaintPanelMainWindow *pNew = new PaintPanelMainWindow;
        pNew->poi = poi;
        pNew->isLineEnd = false;

        pNew->lineColor = lineColor;
        pNew->lineThickness = lineThickness;

        poiList << pNew;
    }
    else
    {
        poi2 = mEvent->pos();
    }
    update();
}

/*** 鼠标释放 */
void PaintPanelMainWindow::mouseReleaseEvent(QMouseEvent *mEvent)
{
    /*** 如果是画笔状态 */
    if(shape == 3)
    {
        /*** 画笔 */
        poi = mEvent->pos();
        PaintPanelMainWindow *pNew = new PaintPanelMainWindow;
        pNew->poi = poi;
        pNew->isLineEnd = true;

        pNew->lineColor = lineColor;
        pNew->lineThickness = lineThickness;

        poiList << pNew;
    }
    else
    {
        poi2 = mEvent->pos();

        PaintPanelMainWindow *pNew = new PaintPanelMainWindow;

        pNew->poi1 = poi1;
        pNew->poi2 = poi2;

        pNew->shape = ui->shapSelectComboBox->currentIndex();

        /*** 得到现在线条的颜色 */
        pNew->lineColor = lineColor;
        pNew->fillColor = fillColor;

        pNew->lineThickness = ui->lineSelectSpinBox->value();


        /** 把这个对象写入链表中 */
        picList << pNew;
    }


}

/*** 得到线条的粗细 */
void PaintPanelMainWindow::on_lineSelectSpinBox_valueChanged(const QString &arg1)
{
    lineThickness = arg1.toInt();
}

void PaintPanelMainWindow::on_shapSelectComboBox_currentIndexChanged(int index)
{
    shape = index;
    /*** 如果是直线或者写字状态，没有填充色 */
    if(shape == 0 || shape == 3)
    {
        ui->fillColorPushButton->setDisabled(true);
    }
    else
    {
        ui->fillColorPushButton->setEnabled(true);
    }
}



/*** 清屏 */
void PaintPanelMainWindow::on_clearPushButton_clicked()
{
    /*** 删除链表 */
    while (!picList.isEmpty())
        delete picList.takeFirst();

    /*** 删除链表 */
    while (!poiList.isEmpty())
        delete poiList.takeFirst();

    /*** 把清屏状态位置为true */
    isClear = true;
    update();
}

/*** 回退按钮 */
void PaintPanelMainWindow::on_delPushButton_clicked()
{
    /*** 判断链表是否为空 */
    if(!picList.isEmpty())
    {
        delete picList.takeLast();
    }

    isClear = true;
    update();
}

