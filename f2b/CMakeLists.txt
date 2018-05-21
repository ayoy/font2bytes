cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

project(f2b)

find_package(PNG REQUIRED)
include_directories(.
        ${PNG_INCLUDE_DIR})

set(TARGET)

FILE(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_library(${PROJECT_NAME} SHARED
        ${headers}
        convertererror.cpp
        fixedconverter.cpp
        sourcecodegenerator.cpp)

target_link_libraries(${PROJECT_NAME} png)
target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(${PROJECT_NAME} PROPERTIES
        SOVERSION 1.0.0)

INSTALL(FILES ${headers} DESTINATION include/f2b)
INSTALL(FILES include/f2b.h DESTINATION include)
INSTALL(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib)
