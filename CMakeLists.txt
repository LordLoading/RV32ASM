cmake_minimum_required(VERSION 3.31)
project(RV32ASM)

set(CMAKE_CXX_STANDARD 20)

add_executable(RV32ASM main.cpp
        src/dUtils.h
        src/LabelSection.h
        src/utils.h
        src/instructionStuff/parse/parseIALUType.h
        src/instructionStuff/iUtils.h
        src/instructionStuff/parse/parseLType.h
        src/instructionStuff/assembleLine.h
        src/instructionStuff/parse/parseSType.h
        src/instructionStuff/parse/parseBType.h
        src/instructionStuff/parse/parseJType.h
        src/instructionStuff/parse/parseUType.h
        src/instructionStuff/parse/parseEnvType.h
)
