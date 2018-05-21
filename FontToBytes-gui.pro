TEMPLATE = subdirs

CONFIG += ordered

QMAKE_SUBSTITUTES += .qmake.cache.in

SUBDIRS = \
    f2b \
    gui
