//
// Created by lor on 8/21/25.
//

#ifndef PARSESTYPE_H
#define PARSESTYPE_H
#include <sstream>
#include <string>
#include <vector>

#include "../../lookup/reg.h"
#include "../../utils.h"
#include "../../dUtils.h"
#include "../iUtils.h"

class LabelSection;

std::string parseSType(inst::structThing inst, std::string str, std::vector<LabelSection> labels) {
    str.erase(0, str.find(' '));

    int bin = 0;

    std::stringstream strStream(str);
    std::string intermediate;
    std::vector<std::string> tokens;

    while (std::getline(strStream, intermediate, ',')) {
        tokens.push_back(utils::getFirstWord(intermediate));
    }

    iUtils::offset offset = iUtils::splitOffset(tokens[1]);
    int imm = dUtils::parseAuto(offset.data, labels);

    bin |= 0x7f & inst.opcode;
    bin |= (0x1f & imm) << 7;
    bin |= (0x7 & inst.funct3) << (12);
    bin |= (0x1f & regs::parse(offset.reg)) << 15;
    bin |= (0x1f & regs::parse(tokens[0])) << 20;
    bin |= (0x7f & (imm >> 5)) << 25;

    return iUtils::intToString(bin);
}

#endif
