QT += widgets multimedia

TEMPLATE = lib
DEFINES += TERMINAL_LIBRARY

CONFIG += c++17 plugin

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEPENDS += iplugin iwidget

DEPEND_PLUGINS += menubar statusbar

3RDPARTY += qtermwidget qsourcehighlite libptyqt
include($$common)
SOURCES += \
    iterminal.cpp \
    terminaldockwidget.cpp \
    terminaltabwidget.cpp \
    terminalwidget.cpp

HEADERS += \
    terminal_global.h \
    iterminal.h \
    terminaldockwidget.h \
    terminaltabwidget.h \
    terminalwidget.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
