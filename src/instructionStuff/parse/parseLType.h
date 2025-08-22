//
// Created by loading on 19.08.2025.
//

#ifndef PARSELTYPE_H
#define PARSELTYPE_H

#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "../iUtils.h"
#include "../../dUtils.h"
#include "../../lookup/reg.h"

std::string parseLType(inst::structThing inst, std::string str, std::vector<LabelSection> labels) {
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
    bin |= (0x1f & regs::parse(tokens[0])) << 7;
    bin |= (0x7 & inst.funct3) << (12);
    iUtils::offset offset = iUtils::splitOffset(tokens[1]);
    bin |= (0x1f & regs::parse(offset.reg)) << (15);
    bin |= (0xfff & dUtils::parseAuto(offset.data, std::move(labels))) << (20);

    return iUtils::intToString(bin);
}

#endif
