#-------------------------------------------------
#
# Project created by QtCreator 2013-05-01T17:24:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simple-qt-thread-example
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    producer.cpp consumer.cpp work.cpp flow.cpp

HEADERS  += mainwindow.h \
    producer.h consumer.h work.h flow.h

FORMS    += mainwindow.ui
