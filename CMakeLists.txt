cmake_minimum_required(VERSION 3.31)
project(RV32ASM)

set(CMAKE_CXX_STANDARD 20)

add_executable(RV32ASM main.cpp
        src/dUtils.h
        src/LabelSection.h
        src/utils.h
        src/instructionParsers/parseIALUType.h
        src/instructionParsers/iUtils.h
        src/instructionParsers/parseLType.h
)
