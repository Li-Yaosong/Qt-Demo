#-------------------------------------------------
#
# Project created by QtCreator 2017-10-31T00:37:59
#
#-------------------------------------------------

QT       += core gui network multimedia serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
# DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17
3RDPARTY += qtermwidget qsourcehighlite libptyqt

include($$common)
include($$PWD/../../lib/3rdparty/qfonticon/QFontIcon/QFontIcon.pri)
INCLUDEPATH += \
    $$PWD \
    $$PWD/sessionswindow
SOURCES += \
        main.cpp \
    remoteterm.cpp \
    sessionswindow/sessionswindow.cpp

HEADERS += \
    remoteterm.h \
    sessionswindow/sessionswindow.h

LIBS += -ladvapi32

