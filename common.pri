ILIBS += \
    iplugin \
    iwidget \
    hdc

IPLUGINS += \
    editor \
    toolbar \
    menubar \
    statusbar \
    output

!isEmpty(DEPEND_PLUGINS) {
    LIBS += -L$${plugin_dir}
}
INCLUDEPATH += $${top_dir}/app

for(lib, ILIBS) {
    contains(DEPENDS, $$lib) {
        INCLUDEPATH += $${top_dir}/lib/$$lib
        LIBS += -L$${lib_dir}/$$lib -l$$lib
    }
}

for(plugin, IPLUGINS) {
    contains(DEPEND_PLUGINS, $$plugin) {
        INCLUDEPATH += $${top_dir}/plugins/$$plugin
        LIBS += -l$$plugin
    }
}

plugin {
    DESTDIR = $${lib_out}/plugins
    DISTFILES += \
        $$PWD/plugins/$${TARGET}/$${TARGET}.json
}
else {
    DESTDIR = $${lib_dir}/$${TARGET}
}

contains(3RDPARTY, qsourcehighlite) {
    INCLUDEPATH +=  \
        $${top_dir}/lib/3rdparty/qsourcehighlite

    LIBS += -L$${lib_dir}/qsourcehighlite -lqsourcehighlite
}

contains(3RDPARTY, qtermwidget) {
    INCLUDEPATH +=  \
        $${top_dir}/lib/3rdparty/qtermwidget \
        $${top_dir}/lib/3rdparty/qtermwidget/lib

    LIBS += -L$${lib_dir}/qtermwidget -lqtermwidget -ladvapi32
}

contains(3RDPARTY, libptyqt) {
    INCLUDEPATH +=  \
        $${top_dir}/lib/3rdparty/libptyqt

    LIBS += -L$${lib_dir}/libptyqt -llibptyqt -ladvapi32
}

contains(3RDPARTY, qcodeeditor) {
    INCLUDEPATH +=  \
        $${top_dir}/lib/3rdparty/qcodeeditor \
        $${top_dir}/lib/3rdparty/qcodeeditor/include \
        $${top_dir}/lib/3rdparty/qcodeeditor/include/internal

    LIBS += -L$${lib_dir}/qcodeeditor -lqcodeeditor
}
