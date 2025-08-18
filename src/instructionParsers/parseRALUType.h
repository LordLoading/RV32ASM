//
// Created by loading on 17.08.2025.
//

#ifndef PARSERALUTYPE_H
#define PARSERALUTYPE_H
#include <sstream>
#include <string>
#include <vector>

#include "iUtils.h"

std::string parseRALUType(iUtils::instruction inst, std::string str) {
    str.erase(0, str.find(" "));

    int bin = 0;

    std::stringstream strStream(str);
    std::string intermediate;
    std::vector<std::string> tokens;

    while (std::getline(strStream, intermediate, ',')) {
        tokens.push_back(utils::getFirstWord(intermediate));
    }

    bin |= (0x7f & inst.opcode);
    std::cout << std::hex << inst.opcode << std::endl;
    bin |= (0x1f & iUtils::parseReg(tokens[0])) << 7;
    bin |= (0x7 & inst.funct3) << (12);
    bin |= (0x1f & iUtils::parseReg(tokens[1])) << (15);
    bin |= (0x1f & iUtils::parseReg(tokens[2])) << (20);
    bin |= (0x7f & inst.funct7) << (25);

    return iUtils::intToString(bin);
}

#endif //PARSEITYPE_H
