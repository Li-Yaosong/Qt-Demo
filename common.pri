ILIBS += \
    iplugin \
    iwidget

IPLUGINS += \
    editor \
    toolbar \
    menubar \
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

# contains(3RDPARTY, qscintilla) {
#     INCLUDEPATH +=  \
#         $${top_dir}/lib/3rdparty/qscintilla \
#         $${top_dir}/lib/3rdparty/qscintilla/Qsci

#     LIBS += -L$${lib_dir}/qscintilla -lqscintilla
# }
