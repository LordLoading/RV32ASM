cmake_minimum_required(VERSION 3.31)
project(RV32ASM)

set(CMAKE_CXX_STANDARD 20)

add_executable(RV32ASM main.cpp
        src/DataParser.h
        src/LabelSection.cpp
        src/utils.h
)
