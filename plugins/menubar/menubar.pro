QT += widgets

TEMPLATE = lib
DEFINES += MENUBAR_LIBRARY

CONFIG += c++17 plugin

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEPENDS += iplugin iwidget

include($$common)
SOURCES += \
    filemenu.cpp \
    helpmenu.cpp \
    imenubar.cpp \
    menubar.cpp \
    menubarmanager.cpp \
    viewmenu.cpp

HEADERS += \
    filemenu.h \
    helpmenu.h \
    menubar.h \
    menubar_global.h \
    imenubar.h \
    menubarmanager.h \
    viewmenu.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    menubar.json
