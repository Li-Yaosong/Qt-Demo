QT += core

CONFIG += c++17
TEMPLATE = lib
CONFIG += static
DESTDIR = $${lib_dir}/$${TARGET}

HEADERS += \
    iptyprocess.h \
    ptyqt.h \

SOURCES += \
    ptyqt.cpp \

win32:{
    win32-g++ {
        HEADERS += $$PWD/winptyprocess.h
        SOURCES += $$PWD/winptyprocess.cpp
    }
    win32-msvc*{
        HEADERS += $$PWD/conptyprocess.h
        SOURCES += $$PWD/conptyprocess.cpp
        LIBS += -lAdvapi32
    }
    LIBS += -lwsock32 -lws2_32 -lcrypt32 -liphlpapi -lnetapi32 -lversion -lwinmm -luserenv -ladvapi32
}
unix {
    HEADERS += \
        unixptyprocess.h

    SOURCES += \
        unixptyprocess.cpp
    LIBS += -lpthread -ldl
}
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


