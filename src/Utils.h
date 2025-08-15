//
// Created by lor on 8/14/25.
//

#ifndef UTILS_H
#define UTILS_H

#pragma once

#include <string>
#include <vector>

namespace Utils {
    struct instruction {
        std::string name;
        std::string fmt;
        int opcode;
        int funct3;
        int funct7;
    };

    std::vector<instruction> instructions = {
        //alu
        {"add",     "r", 0b0110011, 0x0, 0x00},
        {"sub",     "r", 0b0110011, 0x0, 0x20},
        {"xor",     "r", 0b0110011, 0x4, 0x00},
        {"or",      "r", 0b0110011, 0x6, 0x00},
        {"and",     "r", 0b0110011, 0x7, 0x00},
        {"sll",     "r", 0b0110011, 0x1, 0x00},
        {"srl",     "r", 0b0110011, 0x5, 0x00},
        {"sra",     "r", 0b0110011, 0x5, 0x20},
        {"slt",     "r", 0b0110011, 0x2, 0x00},
        {"sltu",    "r", 0b0110011, 0x3, 0x00},
        //alu immediate
        {"addi",    "i", 0b0010011, 0x0, 0x00},
        {"xori",    "i", 0b0010011, 0x4, 0x00},
        {"ori",     "i", 0b0010011, 0x6, 0x00},
        {"andi",    "i", 0b0010011, 0x7, 0x00},
        {"slli",    "i", 0b0010011, 0x1, 0x00},
        {"srli",    "i", 0b0010011, 0x5, 0x00},
        {"srai",    "i", 0b0010011, 0x5, 0x20},
        {"slti",    "i", 0b0010011, 0x2, 0x00},
        {"sltui",   "i", 0b0010011, 0x3, 0x00},
        //load
        {"lb",      "i", 0b0000011, 0x0, 0x00},
        {"lh",      "i", 0b0000011, 0x1, 0x00},
        {"lw",      "i", 0b0000011, 0x2, 0x00},
        {"lbu",     "i", 0b0000011, 0x4, 0x00},
        {"lhu",     "i", 0b0000011, 0x5, 0x00},
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
        {"jalr",    "i", 0b1100111, 0x0, 0x00},
        //upper
        {"lui",     "u", 0b0110111, 0x0, 0x00},
        {"auipc",   "u", 0b0010111, 0x0, 0x00},
        //sys stuff
        {"ecall",   "i", 0b1110011, 0x0, 0x00},
        {"ebreak",  "i", 0b1110011, 0x0, 0x01},
        //m extension
        {"mul",     "r", 0b0110011, 0x0, 0x01},
        {"mulh",    "r", 0b0110011, 0x1, 0x01},
        {"mulsu",   "r", 0b0110011, 0x2, 0x01},
        {"mulu",    "r", 0b0110011, 0x3, 0x01},
        {"div",     "r", 0b0110011, 0x4, 0x01},
        {"rem",     "r", 0b0110011, 0x5, 0x01},
        {"remu",    "r", 0b0110011, 0x6, 0x01},
    };

    std::string getFirstWord(std::string str) {
        int start = str.find_first_not_of("\t ");
        str = str.substr(start, str.size());
        return str.substr(0, str.find_first_of("\t "));
    }

    bool isInstruction(const std::string& str) {
        bool found = false;
        for (const instruction& inst : instructions) {
            if (inst.name == getFirstWord(str)) {
                found = true;
                break;
            }
        }

        return found;
    };

    int getLineSize(std::string line) {
        if (getFirstWord(line) == ".byte") return 1;
        if (getFirstWord(line) == ".half") return 2;
        if (getFirstWord(line) == ".word") return 4;
        if (getFirstWord(line) == ".string") {
            int firstChar = line.find_first_of("\"");
            int secondChar = line.find("\"", firstChar + 1);
            return secondChar - firstChar;
        }

        if (isInstruction(line)) return 4;

        return 0;
    }
}

#endif //UTILS_H
