#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_openNote_clicked();

    void on_openRss_clicked();

    void on_openClassTable_clicked();

    void on_openEmail_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
