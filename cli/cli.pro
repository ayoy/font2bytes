TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

include(../common.pri)

TARGET = f2b

F2B_LIB = font2bytes

macx: {
    LIBS += -L/usr/local/lib -lpng -L$$OUT_PWD/../$${TARGET} -l$${F2B_LIB}
    INCLUDEPATH += /usr/local/include $$PWD/../f2b
    QMAKE_LFLAGS += -Wl,-rpath,$$OUT_PWD/../$${F2B_LIB}
    CONFIG(debug, debug|release) {
        QMAKE_POST_LINK += install_name_tool -change lib$${F2B_LIB}.1.dylib \
                           ../f2b/lib$${F2B_LIB}.1.dylib $${TARGET}
    }
} else: unix {
    INCLUDEPATH += /usr/local/include $$PWD/../f2b
    LIBS += -L/usr/local/lib -lpng -L$$OUT_PWD/../$${TARGET} -l$${F2B_LIB}
    QMAKE_LFLAGS += -Wl,-rpath,.:$${INSTALL_PREFIX}/lib$${LIB_SUFFIX}
}

SOURCES += \
    png_read.c \
    main.cpp \
    inputpngimage.cpp

HEADERS += \
    png_read.h \
    inputpngimage.h
