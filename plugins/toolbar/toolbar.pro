QT += widgets

TEMPLATE = lib
DEFINES += TOOLBAR_LIBRARY

CONFIG += c++17 plugin
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEPENDS += iplugin iwidget

DEPEND_PLUGINS += menubar

include($$common)
SOURCES += \
    itoolbar.cpp \
    toolbarmanager.cpp

HEADERS += \
    toolbar_global.h \
    itoolbar.h \
    toolbarmanager.h
# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
