TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

TARGET = font2bytes

macx: {
    LIBS += -L/usr/local/lib -lpng -L$$OUT_PWD/../f2b -lf2b
    INCLUDEPATH += /usr/local/include $$PWD/../f2b
    QMAKE_LFLAGS += -Wl,-rpath,$$OUT_PWD/../f2b
    CONFIG(debug, debug|release) {
        QMAKE_POST_LINK += install_name_tool -change libf2b.1.dylib \
                           ../f2b/libf2b.1.dylib $${TARGET}
    }
}

SOURCES += \
    png_read.c \
    main.cpp \
    inputpngimage.cpp

HEADERS += \
    png_read.h \
    inputpngimage.h
