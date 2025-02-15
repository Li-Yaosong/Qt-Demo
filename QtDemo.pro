TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += \
    lib \
    plugins \
    app \
    test

# 定义源目录和目标目录
SRC_DIR = $$replace(PWD, /, \\)\toolchains

DST_DIR = $$replace(lib_out, /, \\)\toolchains
message($$QMAKE_COPY_DIR $$SRC_DIR $$DST_DIR)
system($$QMAKE_COPY_DIR $$SRC_DIR $$DST_DIR)

DISTFILES += $$PWD/.qmake.conf
