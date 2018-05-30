QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = font2bytes
TEMPLATE = app
VERSION = 1.0.0

include(../common.pri)

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += $$PWD/../f2b ui conv
DEPENDPATH += $$PWD/../f2b

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../f2b/release/ -lf2b
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../f2b/debug/ -lf2b
else:macx: LIBS += -L$${TARGET}.app/Contents/Frameworks -lf2b
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

macx: ICON = macx/font2bytes.icns
else:unix: {
    icons16.path = $${INSTALL_PREFIX}/share/icons/hicolor/16x16/apps
    icons16.files = x11/icons/16x16/font2bytes.png
    icons22.path = $${INSTALL_PREFIX}/share/icons/hicolor/22x22/apps
    icons22.files = x11/icons/22x22/font2bytes.png
    icons32.path = $${INSTALL_PREFIX}/share/icons/hicolor/32x32/apps
    icons32.files = x11/icons/32x32/font2bytes.png
    icons48.path = $${INSTALL_PREFIX}/share/icons/hicolor/48x48/apps
    icons48.files = x11/icons/48x48/font2bytes.png
    icons64.path = $${INSTALL_PREFIX}/share/icons/hicolor/64x64/apps
    icons64.files = x11/icons/64x64/font2bytes.png
    icons128.path = $${INSTALL_PREFIX}/share/icons/hicolor/128x128/apps
    icons128.files = x11/icons/128x128/font2bytes.png
    icons256.path = $${INSTALL_PREFIX}/share/icons/hicolor/256x256/apps
    icons256.files = x11/icons/256x256/font2bytes.png
    desktop.path = $${INSTALL_PREFIX}/share/applications
    desktop.files = x11/font2bytes.desktop
    INSTALLS += target \
        icons \
        icons16 \
        icons22 \
        icons32 \
        icons48 \
        icons64 \
        icons128 \
        icons256 \
        desktop
}
