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
    keep/sources/showwidget.cpp \
    Classtable/sources/assist.cpp \
    Classtable/sources/classtable.cpp \
    Classtable/sources/email.cpp \
    Classtable/sources/mydialog.cpp \
    Classtable/sources/newclass.cpp \
    Classtable/sources/newpro.cpp \
    Classtable/sources/newtable.cpp \
    Classtable/sources/newtutor.cpp \
    Classtable/sources/problem.cpp \
    Classtable/sources/table.cpp \
    Classtable/sources/tutor.cpp

HEADERS  += mainwindow.h \
    Rss/headers/channel.h \
    Rss/headers/dbmanager.h \
    Rss/headers/item.h \
    Rss/headers/rssreader.h \
    keep/headers/imageprocessor.h \
    keep/headers/paintpanelmainwindow.h \
    keep/headers/picture.h \
    keep/headers/showpicture.h \
    keep/headers/showwidget.h \
    Classtable/headers/assist.h \
    Classtable/headers/classtable.h \
    Classtable/headers/connection.h \
    Classtable/headers/email.h \
    Classtable/headers/mydialog.h \
    Classtable/headers/newclass.h \
    Classtable/headers/newpro.h \
    Classtable/headers/newtable.h \
    Classtable/headers/newtutor.h \
    Classtable/headers/problem.h \
    Classtable/headers/table.h \
    Classtable/headers/tutor.h

FORMS    += mainwindow.ui \
    Rss/forms/rssreader.ui \
    keep/forms/picture.ui \
    keep/forms/notemainwindow.ui \
    keep/forms/notepaintpanelmainwindow.ui \
    Classtable/forms/classtable.ui \
    Classtable/forms/newclass.ui \
    Classtable/forms/newpro.ui \
    Classtable/forms/newtable.ui \
    Classtable/forms/newtutor.ui

QT     += webkitwidgets
QT     += sql

RESOURCES += \
    Rss/RssResources.qrc \
    keep/images/KeepResources.qrc
