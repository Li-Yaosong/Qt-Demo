QT += widgets openglwidgets concurrent

TEMPLATE = lib
DEFINES += OHREMOTE_LIBRARY

CONFIG += c++17 plugin

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEPENDS += iplugin iwidget hdc

DEPEND_PLUGINS += toolbar

include($$common)
SOURCES += \
    ohremote.cpp \
    ohremotepage.cpp \
    ohscreendisplay.cpp

HEADERS += \
    ohremote_global.h \
    ohremote.h \
    ohremotepage.h \
    ohscreendisplay.h

LIBS += -lopengl32
# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
