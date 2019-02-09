QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../common.pri)

TARGET = $${GUI_TARGET}
TEMPLATE = app
VERSION = 1.0.0



DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += $$PWD/../lib ui conv
DEPENDPATH += $$PWD/../lib

F2B_LIB = font2bytes

win32:CONFIG(release, debug|release): LIBS += -L$${DESTDIR}/release/ -l$${F2B_LIB}
else:win32:CONFIG(debug, debug|release): LIBS += -L$${DESTDIR}/debug/ -l$${F2B_LIB}
else:macx: LIBS += -L$${DESTDIR}/$${TARGET}.app/Contents/Frameworks -l$${F2B_LIB}
else:unix {
    LIBS += -L$${DESTDIR} -l$${F2B_LIB}
    QMAKE_LFLAGS += -Wl,-rpath,.:build:$${INSTALL_PREFIX}/lib$${LIB_SUFFIX}
}

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
    conv/inputqimage.cpp \
    conv/conversionservice.cpp

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
    conv/inputqimage.h \
    conv/conversionservice.h

FORMS += \
    ui/mainwindow.ui

macx: ICON = macx/font2bytes.icns
else:unix: {
    target.path = $${INSTALL_PREFIX}/bin
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
        icons16 \
        icons22 \
        icons32 \
        icons48 \
        icons64 \
        icons128 \
        icons256 \
        desktop
}

RESOURCES += \
    assets.qrc
