cmake_minimum_required(VERSION 3.10)
project(cli)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(cli
        inputpngimage.cpp
        inputpngimage.h
        main.cpp
        png_read.c
        png_read.h)

target_link_libraries (cli LINK_PUBLIC f2b)