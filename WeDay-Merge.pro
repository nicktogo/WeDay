#-------------------------------------------------
#
# Project created by QtCreator 2016-01-09T23:59:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WeDay-Merge
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Rss/sources/channel.cpp \
    Rss/sources/dbmanager.cpp \
    Rss/sources/item.cpp \
    Rss/sources/rssreader.cpp \
    keep/sources/imageprocessor.cpp \
    keep/sources/paintpanelmainwindow.cpp \
    keep/sources/picture.cpp \
    keep/sources/showpicture.cpp \
    keep/sources/showwidget.cpp

HEADERS  += mainwindow.h \
    Rss/headers/channel.h \
    Rss/headers/dbmanager.h \
    Rss/headers/item.h \
    Rss/headers/rssreader.h \
    keep/headers/imageprocessor.h \
    keep/headers/paintpanelmainwindow.h \
    keep/headers/picture.h \
    keep/headers/showpicture.h \
    keep/headers/showwidget.h

FORMS    += mainwindow.ui \
    Rss/forms/rssreader.ui \
    keep/forms/picture.ui \
    keep/forms/notemainwindow.ui \
    keep/forms/notepaintpanelmainwindow.ui

QT     += webkitwidgets
QT     += sql

RESOURCES += \
    Rss/RssResources.qrc \
    keep/images/KeepResources.qrc
