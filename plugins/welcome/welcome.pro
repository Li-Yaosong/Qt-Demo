QT += widgets

TEMPLATE = lib
DEFINES += WELCOME_LIBRARY

CONFIG += c++17 plugin

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEPENDS += iplugin iwidget

DEPEND_PLUGINS += toolbar

include($$common)
SOURCES += \
    welcome.cpp \
    welcomepage.cpp

HEADERS += \
    welcome_global.h \
    welcome.h \
    welcomepage.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
