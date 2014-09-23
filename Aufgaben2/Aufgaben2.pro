#-------------------------------------------------
#
# Project created by QtCreator 2014-08-01T12:45:41
#
#-------------------------------------------------

QT       += core gui widgets
QT -= core gui
CONFIG += console
TARGET = Aufgaben2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h cvmattoqimage.h

FORMS    += mainwindow.ui

include(opencv.pri)

