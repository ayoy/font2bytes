#-------------------------------------------------
#
# Project created by QtCreator 2018-05-15T22:03:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FontToBytes
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += lib ui

SOURCES += \
    main.cpp \
    ui/mainwindow.cpp \
    ui/droplabel.cpp \
    ui/droppablestackedwidget.cpp \
    conversionconfig.cpp \
    imageconverter.cpp \
    conversionrunnable.cpp \
    lib/sourcecodegenerator.cpp \
    inputqimage.cpp \
    lib/fixedconverter.cpp \
    lib/convertererror.cpp \
    ui/promptlabel.cpp \
    ui/shakeanimation.cpp

HEADERS += \
    ui/mainwindow.h \
    ui/droplabel.h \
    ui/droppablestackedwidget.h \
    conversionconfig.h \
    imageconverter.h \
    conversionrunnable.h \
    lib/bytewriter.h \
    lib/sourcecodegenerator.h \
    lib/inputimage.h \
    inputqimage.h \
    lib/fontconverter.h \
    lib/fixedconverter.h \
    lib/convertererror.h \
    ui/promptlabel.h \
    ui/shakeanimation.h

FORMS += \
        ui/mainwindow.ui
