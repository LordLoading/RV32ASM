//
// Created by lor on 8/22/25.
//

#include "parser/instruction/j_type.h"

#include <string>
#include <vector>
#include <sstream>

#include "utils/instruction.h"
#include "utils/data.h"
#include "lookup/register.h"
#include "utils/common.h"

std::string parseJType(const inst::structThing& inst, const std::string& str) {
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

    int imm = dUtils::parseAuto(tokens[1]);

    bin |= 0x7f & inst.opcode;
    bin |= (0x1f & regs::parse(tokens[0])) << 7;
    bin |= (0x0ff & (imm >> 12)) << 12;
    bin |= (0x1 & (imm >> 11)) << 20;
    bin |= (0x3ff & (imm >> 1)) << 21;
    bin |= (0x1 & (imm >> 20)) << 31;

    return iUtils::intToString(bin);
}
