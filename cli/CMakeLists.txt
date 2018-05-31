cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 11)

set(TARGET f2b)

add_executable(${TARGET}
        inputpngimage.cpp
        inputpngimage.h
        main.cpp
        png_read.c
        png_read.h)

target_include_directories(${TARGET} PRIVATE .)
target_link_libraries (${TARGET} LINK_PUBLIC font2bytes)
set_target_properties(${TARGET} PROPERTIES 
        INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

INSTALL(TARGETS ${TARGET}
        RUNTIME DESTINATION bin)
