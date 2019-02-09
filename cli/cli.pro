TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

include(../common.pri)

TARGET = f2b

F2B_LIB = font2bytes

macx: {
    LIBS += -L/usr/local/lib -lpng -L$${DESTDIR} -l$${F2B_LIB}
    INCLUDEPATH += /usr/local/include $$PWD/../lib
    QMAKE_LFLAGS += -Wl,-rpath,$${DESTDIR}
    QMAKE_POST_LINK += install_name_tool -change lib$${F2B_LIB}.1.dylib \
                       @rpath/lib$${F2B_LIB}.1.dylib $${DESTDIR}/$${TARGET}
} else: unix {
    INCLUDEPATH += /usr/local/include $$PWD/../lib
    LIBS += -L/usr/local/lib -lpng -L$$OUT_PWD/../$${TARGET} -l$${F2B_LIB}
    QMAKE_LFLAGS += -Wl,-rpath,.:build:$${INSTALL_PREFIX}/lib$${LIB_SUFFIX}
}

SOURCES += \
    png_read.c \
    main.cpp \
    inputpngimage.cpp

HEADERS += \
    png_read.h \
    inputpngimage.h
