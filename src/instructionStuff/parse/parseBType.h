//
// Created by lor on 8/22/25.
//

#ifndef PARSEBTYPE_H
#define PARSEBTYPE_H
#include <iosfwd>
#include <vector>
#include <sstream>

#include "../iUtils.h"
#include "../../lookup/reg.h"
#include "../../lookup/inst.h"
#include "../../dUtils.h"

std::string parseBType(inst::structThing inst, std::string str) {
    str.erase(0 ,str.find_first_not_of("   "));
    str.erase(0, str.find(' '));

    int bin = 0;

    std::stringstream strStream(str);
    std::string intermediate;
    std::vector<std::string> tokens;

    while (std::getline(strStream, intermediate, ',')) {
        tokens.push_back(utils::getFirstWord(intermediate));
    }

    bin |= 0x7f & inst.opcode;
    bin |= (0x1 & (dUtils::parseAuto(tokens[2]) >> 11)) << 7;
    bin |= (0x1e & dUtils::parseAuto(tokens[2])) << 7;
    bin |= (0x7 & inst.funct3) << (12);
    bin |= (0x1f & regs::parse(tokens[0])) << (15);
    bin |= (0x1f & regs::parse(tokens[1])) << (20);
    bin |= (0x3f & (dUtils::parseAuto(tokens[2]) >> 5)) << (25);
    bin |= (0x1 & (dUtils::parseAuto(tokens[2]) >> 12)) << 31;

    return iUtils::intToString(bin);
}

#endif
