TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

macx: {
    LIBS += -L/usr/local/lib -lpng -L$$OUT_PWD/../f2b -lf2b
    INCLUDEPATH += /usr/local/include $$PWD/../f2b
    QMAKE_LFLAGS += -Wl,-rpath,$$OUT_PWD/../f2b
}

SOURCES += \
    png_read.c \
    main.cpp \
    inputpngimage.cpp

HEADERS += \
    png_read.h \
    inputpngimage.h
