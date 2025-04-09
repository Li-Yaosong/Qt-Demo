QT -= gui
QT += widgets

TEMPLATE = lib
DEFINES += EDITOR_LIBRARY

CONFIG += c++17 plugin

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEPENDS += iplugin iwidget

DEPEND_PLUGINS += toolbar menubar

3RDPARTY += qsourcehighlite qcodeeditor

include($$common)
SOURCES += \
    editorpage.cpp \
    ieditor.cpp

HEADERS += \
    editor_global.h \
    editorpage.h \
    ieditor.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    editor.json
