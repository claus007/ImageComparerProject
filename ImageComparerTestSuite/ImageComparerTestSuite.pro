#-------------------------------------------------
#
# Project created by QtCreator 2013-07-24T19:58:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageComparerTestSuite
TEMPLATE = app


SOURCES += main.cpp\
        Dialog.cpp

HEADERS  += Dialog.h

FORMS    += Dialog.ui

RESOURCES += \
    images.qrc

LIBS += -L ../build -l ImageComparer
INCLUDEPATH += ../ImageComparer \
    ..
