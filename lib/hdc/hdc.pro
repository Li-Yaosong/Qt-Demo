QT += core gui concurrent

TEMPLATE = lib
DEFINES += HDC_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
3RDPARTY += libptyqt
include($$common)
SOURCES += \
    hdc.cpp \
    ohscreenmirror.cpp

HEADERS += \
    hdc_global.h \
    hdc.h \
    ohscreenmirror.h

