TEMPLATE = subdirs

CONFIG += ordered

QMAKE_SUBSTITUTES += .qmake.cache.in

unix: !mac {
    UNAME = $$system(uname -m)
    contains( UNAME, x86_64 ): LIB_SUFFIX = 64
    isEmpty( PREFIX ):INSTALL_PREFIX = /usr
    else:INSTALL_PREFIX = $${PREFIX}
}

SUBDIRS = \
    f2b \
    gui
