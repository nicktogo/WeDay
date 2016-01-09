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
    Classtable/sources/mydialog.cpp \
    Classtable/sources/newclass.cpp \
    Classtable/sources/newpro.cpp \
    Classtable/sources/newtable.cpp \
    Classtable/sources/newtutor.cpp \
    Classtable/sources/problem.cpp \
    Classtable/sources/table.cpp \
    Classtable/sources/tutor.cpp \
    Email/sources/attachment.cpp \
    Email/sources/contentformat.cpp \
    Email/sources/email.cpp \
    Email/sources/emailinfo.cpp \
    Email/sources/file.cpp \
    Email/sources/html.cpp \
    Email/sources/inlinefile.cpp \
    Email/sources/loginwindow.cpp \
    Email/sources/message.cpp \
    Email/sources/multipart.cpp \
    Email/sources/part.cpp \
    Email/sources/pop3.cpp \
    Email/sources/quotedprintable.cpp \
    Email/sources/sendmail.cpp \
    Email/sources/smtp.cpp \
    Email/sources/text.cpp \
    Classtable/sources/classtableemail.cpp

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
    Classtable/headers/mydialog.h \
    Classtable/headers/newclass.h \
    Classtable/headers/newpro.h \
    Classtable/headers/newtable.h \
    Classtable/headers/newtutor.h \
    Classtable/headers/problem.h \
    Classtable/headers/table.h \
    Classtable/headers/tutor.h \
    Email/headers/attachment.h \
    Email/headers/contentformat.h \
    Email/headers/email.h \
    Email/headers/emailinfo.h \
    Email/headers/file.h \
    Email/headers/global.h \
    Email/headers/html.h \
    Email/headers/inlinefile.h \
    Email/headers/loginwindow.h \
    Email/headers/message.h \
    Email/headers/mimesmtp.h \
    Email/headers/multipart.h \
    Email/headers/part.h \
    Email/headers/pop3.h \
    Email/headers/quotedprintable.h \
    Email/headers/sendmail.h \
    Email/headers/smtp.h \
    Email/headers/text.h \
    Classtable/headers/classtableemail.h

FORMS    += mainwindow.ui \
    Rss/forms/rssreader.ui \
    keep/forms/picture.ui \
    keep/forms/notemainwindow.ui \
    keep/forms/notepaintpanelmainwindow.ui \
    Classtable/forms/classtable.ui \
    Classtable/forms/newclass.ui \
    Classtable/forms/newpro.ui \
    Classtable/forms/newtable.ui \
    Classtable/forms/newtutor.ui \
    Email/forms/email.ui \
    Email/forms/loginwindow.ui \
    Email/forms/sendmail.ui

QT     += webkitwidgets
QT     += sql

RESOURCES += \
    Rss/RssResources.qrc \
    keep/images/KeepResources.qrc
