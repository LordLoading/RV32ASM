//
// Created by loading on 17.08.2025.
//

#ifndef PARSEIALUTYPE_H
#define PARSEIALUTYPE_H
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "iUtils.h"
#include "../dUtils.h"
#include "../lookup/reg.h"

std::string parseIALUType(inst::structThing inst, std::string str, std::vector<LabelSection> labels) {
    str.erase(0, str.find(' '));

    int bin = 0;

    std::stringstream strStream(str);
    std::string intermediate;
    std::vector<std::string> tokens;

    while (std::getline(strStream, intermediate, ',')) {
        tokens.push_back(utils::getFirstWord(intermediate));
    }

    bin |= 0x7f & inst.opcode;
    bin |= (0x1f & regs::parse(tokens[0])) << 7;
    bin |= (0x7 & inst.funct3) << (12);
    bin |= (0x1f & regs::parse(tokens[1])) << (15);
    bin |= (0xfff & dUtils::parseAuto(tokens[2], std::move(labels))) << (20);

    return iUtils::intToString(bin);
}

#endif
