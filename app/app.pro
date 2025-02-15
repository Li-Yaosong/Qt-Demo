QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
include($$common)
DESTDIR =$${bin_dir}
INCLUDEPATH += \
    $${top_dir}/lib/iplugin \
    $${top_dir}/lib/iwidget

LIBS += \
    -L$${lib_dir}/iplugin \
    -L$${lib_dir}/iwidget

LIBS += -liplugin -liwidget
SOURCES += \
    main.cpp

HEADERS += \
    defstruct.h

TRANSLATIONS += \
    app_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
