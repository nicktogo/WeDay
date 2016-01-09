#-------------------------------------------------
#
# Project created by QtCreator 2015-12-24T00:16:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = v2
TEMPLATE = app


SOURCES += main.cpp \
    showwidget.cpp \
    imageprocessor.cpp \
    paintpanelmainwindow.cpp \
    picture.cpp \
    showpicture.cpp

HEADERS  += \
    showwidget.h \
    imageprocessor.h \
    paintpanelmainwindow.h \
    picture.h \
    showpicture.h

FORMS    += mainwindow.ui \
    paintpanelmainwindow.ui \
    picture.ui

RESOURCES += \
    myresources.qrc

DISTFILES += \
    Memo
