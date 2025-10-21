cmake_minimum_required(VERSION 3.31)
project(RV32ASM LANGUAGES CXX ASM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

configure_file(${CMAKE_SOURCE_DIR}/assembleMe.s ${CMAKE_BINARY_DIR}/assembleMe.s COPYONLY)

file(GLOB_RECURSE PROJECT_SOURCES
        "${CMAKE_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_SOURCE_DIR}/include/*.h"
)

add_executable(RV32ASM ${PROJECT_SOURCES})

target_include_directories(RV32ASM PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/include
)

set_property(GLOBAL PROPERTY CMAKE_CONFIGURE_DEPENDS
        "${CMAKE_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_SOURCE_DIR}/include/*.h"
)
