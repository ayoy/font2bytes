isEmpty(GUI_PRI) {
    GUI_PRI = 1

    TOP = $${PWD}

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
