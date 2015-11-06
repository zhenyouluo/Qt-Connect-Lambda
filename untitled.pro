#-------------------------------------------------
#
# Project created by QtCreator 2015-11-06T09:54:06
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_connectlambdatest
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += C++11

TEMPLATE = app


SOURCES += tst_connectlambdatest.cpp \
    object.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    object.h
