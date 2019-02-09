#-------------------------------------------------
#
# Project created by QtCreator 2018-05-20T10:19:06
#
#-------------------------------------------------

QT       -= core gui

TARGET = font2bytes
TEMPLATE = lib
VERSION = 1.0.0

DEFINES += F2B_LIBRARY

DEFINES += QT_DEPRECATED_WARNINGS

include(../common.pri)

# GUI=1 is set by .qmake.cache.in in top-level dir
# It's loaded only by the GUI project, with no effect
# on the CLI build
macx: equals(GUI, "1"): {
    LIBS += -install_name \
            @executable_path/../Frameworks/lib$${TARGET}.$${VERSION}.dylib
    DESTDIR = $${DESTDIR}/$${GUI_TARGET}.app/Contents/Frameworks
} else: unix {
    target.path = $${INSTALL_PREFIX}/lib$${LIB_SUFFIX}
    INSTALLS += target
}

SOURCES += \
    bytewriter.cpp \
    convertererror.cpp \
    fixedconverter.cpp \
    sourcecodegenerator.cpp

HEADERS += \
    bytewriter.h \
    convertererror.h \
    fixedconverter.h \
    fontconverter.h \
    inputimage.h \
    sourcecodegenerator.h \
    f2b.h
