cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

find_package(PNG REQUIRED)
include_directories(.
        ${PNG_INCLUDE_DIR})

add_library(f2b SHARED
        bytewriter.h
        convertererror.cpp
        convertererror.h
        f2b.h
        fixedconverter.cpp
        fixedconverter.h
        fontconverter.h
        inputimage.h
        sourcecodegenerator.cpp
        sourcecodegenerator.h)

target_link_libraries(f2b png)
target_include_directories (f2b PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(f2b PROPERTIES
        SOVERSION 1.0.0)
