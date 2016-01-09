#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Rss/headers/rssreader.h>
#include <keep/headers/imageprocessor.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openNote_clicked()
{
    ImageProcessor *imageProcessor = new ImageProcessor;
    imageProcessor->show();
    //hide();
}

void MainWindow::on_openRss_clicked()
{
    RssReader *rssReader = new RssReader;
    rssReader->show();
    //hide();
}
