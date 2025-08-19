//
// Created by loading on 19.08.2025.
//

#ifndef INST_H
#define INST_H

#include <vector>

struct instruction {
        std::string name;
        std::string fmt;
        int opcode;
        int funct3;
        int funct7;
};

std::vector<instruction> instructions = {
    //alu
    {"add",     "ralu", 0b0110011, 0x0, 0x00},
    {"sub",     "ralu", 0b0110011, 0x0, 0x20},
    {"xor",     "ralu", 0b0110011, 0x4, 0x00},
    {"or",      "ralu", 0b0110011, 0x6, 0x00},
    {"and",     "ralu", 0b0110011, 0x7, 0x00},
    {"sll",     "ralu", 0b0110011, 0x1, 0x00},
    {"srl",     "ralu", 0b0110011, 0x5, 0x00},
    {"sra",     "ralu", 0b0110011, 0x5, 0x20},
    {"slt",     "ralu", 0b0110011, 0x2, 0x00},
    {"sltu",    "ralu", 0b0110011, 0x3, 0x00},
    //alu immediate
    {"addi",    "ialu", 0b0010011, 0x0, 0x00},
    {"xori",    "ialu", 0b0010011, 0x4, 0x00},
    {"ori",     "ialu", 0b0010011, 0x6, 0x00},
    {"andi",    "ialu", 0b0010011, 0x7, 0x00},
    {"slli",    "ialu", 0b0010011, 0x1, 0x00},
    {"srli",    "ialu", 0b0010011, 0x5, 0x00},
    {"srai",    "ialu", 0b0010011, 0x5, 0x20},
    {"slti",    "ialu", 0b0010011, 0x2, 0x00},
    {"sltui",   "ialu", 0b0010011, 0x3, 0x00},
    //load
    {"lb",      "l", 0b0000011, 0x0, 0x00},
    {"lh",      "l", 0b0000011, 0x1, 0x00},
    {"lw",      "l", 0b0000011, 0x2, 0x00},
    {"lbu",     "l", 0b0000011, 0x4, 0x00},
    {"lhu",     "l", 0b0000011, 0x5, 0x00},
    //store
    {"sb",      "s", 0b0100011, 0x0, 0x00},
    {"sh",      "s", 0b0100011, 0x1, 0x00},
    {"sw",      "s", 0b0100011, 0x2, 0x00},
    //branch
    {"beq",     "b", 0b1100011, 0x0, 0x00},
    {"bne",     "b", 0b1100011, 0x1, 0x00},
    {"blt",     "b", 0b1100011, 0x4, 0x00},
    {"bge",     "b", 0b1100011, 0x5, 0x00},
    {"bltu",    "b", 0b1100011, 0x6, 0x00},
    {"bgeu",    "b", 0b1100011, 0x7, 0x00},
    //jump
    {"jal",     "j", 0b1101111, 0x0, 0x00},
    {"jalr",    "ij", 0b1100111, 0x0, 0x00},
    //upper
    {"lui",     "u", 0b0110111, 0x0, 0x00},
    {"auipc",   "u", 0b0010111, 0x0, 0x00},
    //sys stuff
    {"ecall",   "env", 0b1110011, 0x0, 0x00},
    {"ebreak",  "env", 0b1110011, 0x0, 0x01},
    //m extension
    {"mul",     "ralu", 0b0110011, 0x0, 0x01},
    {"mulh",    "ralu", 0b0110011, 0x1, 0x01},
    {"mulsu",   "ralu", 0b0110011, 0x2, 0x01},
    {"mulu",    "ralu", 0b0110011, 0x3, 0x01},
    {"div",     "ralu", 0b0110011, 0x4, 0x01},
    {"rem",     "ralu", 0b0110011, 0x5, 0x01},
    {"remu",    "ralu", 0b0110011, 0x6, 0x01},
};

#endif //INST_H
