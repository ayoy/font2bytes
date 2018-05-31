cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 11)

project(font2bytes)

set(TARGET)

FILE(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_library(${PROJECT_NAME} SHARED
        ${headers}
        convertererror.cpp
        fixedconverter.cpp
        sourcecodegenerator.cpp)

target_link_libraries(${PROJECT_NAME} png)
target_include_directories(${PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	${PNG_INCLUDE_DIR})

set_target_properties(${PROJECT_NAME} PROPERTIES
        SOVERSION 1.0.0
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

INSTALL(FILES ${headers} DESTINATION include/f2b)
INSTALL(FILES include/f2b.h DESTINATION include)
INSTALL(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib)
