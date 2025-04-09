QT       += core

CONFIG += c++17
TEMPLATE = lib
DEFINES += IPLUGIN_LIBRARY
include($$common)

HEADERS += \
    iplugin.h \
    iplugin_global.h \
    pluginmanager.h \
    plugintree.h

SOURCES += \
    iplugin.cpp \
    pluginmanager.cpp \
    plugintree.cpp
