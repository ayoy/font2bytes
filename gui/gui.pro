QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FontToBytes
TEMPLATE = app
VERSION = 1.0.0

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += $$PWD/../f2b ui conv
DEPENDPATH += $$PWD/../f2b

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../f2b/release/ -lf2b
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../f2b/debug/ -lf2b
else:unix: LIBS += -L$$OUT_PWD/../f2b/ -lf2b

SOURCES += \
    main.cpp \
    ui/coloredstatusbar.cpp \
    ui/droplabel.cpp \
    ui/droppablestackedwidget.cpp \
    ui/mainwindow.cpp \
    ui/promptlabel.cpp \
    ui/shakeanimation.cpp \
    conv/conversionconfig.cpp \
    conv/conversionrunnable.cpp \
    conv/imageconverter.cpp \
    conv/inputqimage.cpp

HEADERS += \
    ui/coloredstatusbar.h \
    ui/droplabel.h \
    ui/droppablestackedwidget.h \
    ui/mainwindow.h \
    ui/promptlabel.h \
    ui/shakeanimation.h \
    conv/conversionconfig.h \
    conv/conversionrunnable.h \
    conv/imageconverter.h \
    conv/inputqimage.h

FORMS += \
    ui/mainwindow.ui
