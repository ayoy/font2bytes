isEmpty(COMMON_PRI) {
    COMMON_PRI = 1

    TOP = $${PWD}
    GUI_TARGET = font2bytes
    CONFIG += c++14

    isEmpty( PREFIX ):INSTALL_PREFIX = /usr/local
    else:INSTALL_PREFIX = $${PREFIX}

    unix:!mac {
        UNAME = $$system(uname -m)
        contains( UNAME, x86_64 ): LIB_SUFFIX = 64
    }

    UI_DIR = $${TOP}/build/obj
    MOC_DIR = $${TOP}/build/obj
    RCC_DIR = $${TOP}/build/obj
    OBJECTS_DIR = $${TOP}/build/obj
    INCLUDEPATH += $${TOP} $${TOP}/build/obj
    DESTDIR = $${TOP}/build
}
