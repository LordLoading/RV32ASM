//
// Created by lor on 8/22/25.
//

#ifndef PARSEJTYPE_H
#define PARSEJTYPE_H

#include <string>
#include <vector>
#include <sstream>

#include "../iUtils.h"
#include "../../dUtils.h"
#include "../../lookup/inst.h"
#include "../../lookup/reg.h"
#include "../../utils.h"

std::string parseJType(inst::structThing inst, std::string str) {
    str.erase(0 ,str.find_first_not_of("   "));
    str.erase(0, str.find(' '));

    int bin = 0;

    std::stringstream strStream(str);
    std::string intermediate;
    std::vector<std::string> tokens;

    while (std::getline(strStream, intermediate, ',')) {
        tokens.push_back(utils::getFirstWord(intermediate));
    }

    int imm = dUtils::parseAuto(tokens[1]);

    bin |= 0x7f & inst.opcode;
    bin |= (0x1f & regs::parse(tokens[0])) << 7;
    bin |= (0x0ff & (imm >> 12)) << 12;
    bin |= (0x1 & (imm >> 11)) << 20;
    bin |= (0x3ff & (imm >> 1)) << 21;
    bin |= (0x1 & (imm >> 20)) << 31;

    return iUtils::intToString(bin);
}

#endif
