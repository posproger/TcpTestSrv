#-------------------------------------------------
#
# Project created by QtCreator 2014-12-18T21:20:57
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TcpTestSrv
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mtestcore.cpp \
    mtestserver.cpp \
    mtestthread.cpp

HEADERS  += mainwindow.h \
    mtestcore.h \
    mtestserver.h \
    mtestthread.h


ATPATH = "../AT_Shared"

SOURCES += $$ATPATH/qlclientnetmanager.cpp

HEADERS  += $$ATPATH/at_shared.h \
    $$ATPATH/qlclientnetmanager.h

INCLUDEPATH += ../AT_Shared


FORMS    += mainwindow.ui

