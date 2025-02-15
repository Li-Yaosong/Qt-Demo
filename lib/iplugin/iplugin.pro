QT       += core widgets

CONFIG += c++17
TEMPLATE = lib
DEFINES += IPLUGIN_LIBRARY
DESTDIR = $${lib_dir}/$$TARGET
INCLUDEPATH += \
    $${top_dir}/app

HEADERS += \
    iplugin.h \
    iplugin_global.h \
    pluginmanager.h \
    pluginmanager_p.h \
    plugintree.h

SOURCES += \
    iplugin.cpp \
    pluginmanager.cpp \
    plugintree.cpp
