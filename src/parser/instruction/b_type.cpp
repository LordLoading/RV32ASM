//
// Created by lor on 8/22/25.
//

#include "parser/instruction/b_type.h"
#include <iosfwd>
#include <vector>
#include <sstream>

#include "utils/instruction.h"
#include "lookup/register.h"
#include "utils/data.h"
#include "utils/common.h"

std::string parseBType(const inst::structThing& inst, const std::string& str) {
    std::string localStr = str;
    localStr.erase(0 ,localStr.find_first_not_of("   "));
    localStr.erase(0, localStr.find(' '));

    int bin = 0;

    std::stringstream strStream(localStr);
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
