#ifndef SHOWPICTURE
#define SHOWPICTURE
#include <QWidget>
#include <QLabel>
#include <QImage>

class ShowPicture : public QWidget
{
  Q_OBJECT
public:
  explicit ShowPicture(QWidget *parent = 0);
  QImage img;
  QLabel *imageLabel;

signals:

public slots:
};
#endif // SHOWPICTURE

