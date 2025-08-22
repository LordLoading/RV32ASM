//
// Created by lor on 8/22/25.
//

#ifndef PARSEUTYPE_H
#define PARSEUTYPE_H

#include <sstream>
#include <string>
#include <vector>

#include "../iUtils.h"
#include "../../dUtils.h"
#include "../../lookup/inst.h"
#include "../../lookup/reg.h"
#include "../../utils.h"

std::string parseUType(inst::structThing inst, std::string str) {
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
    bin |= (0x000fffff & (imm)) << 12;

    return iUtils::intToString(bin);
}

#endif //PARSEUTYPE_H
