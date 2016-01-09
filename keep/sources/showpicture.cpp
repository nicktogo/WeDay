#include "keep/headers/showpicture.h"

#include <QHBoxLayout>

ShowPicture::ShowPicture(QWidget *parent) :
  QWidget(parent)
{
  imageLabel = new QLabel;
  imageLabel->setScaledContents(true);

  QHBoxLayout *mainLayout = new QHBoxLayout(this);
  mainLayout->addWidget(imageLabel);
}

