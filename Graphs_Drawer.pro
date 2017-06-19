#-------------------------------------------------
#
# Project created by QtCreator 2017-02-26T06:13:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Graphs_Drawer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Graph.cpp \
    GraphsWidget.cpp \
    OneCoordinateSystemGraphsArea.cpp \
    TwoCoordinateSystemsGraphsArea.cpp \
    GraphsArea.cpp

HEADERS  += mainwindow.h \
    Graph.h \
    GraphsWidget.h \
    OneCoordinateSystemGraphsArea.h \
    TwoCoordinateSystemsGraphsArea.h \
    GraphsArea.h

FORMS    += mainwindow.ui
