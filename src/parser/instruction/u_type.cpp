//
// Created by lor on 8/22/25.
//

#include "parser/instruction/u_type.h"

#include <sstream>
#include <string>
#include <vector>

#include "utils/instruction.h"
#include "utils/data.h"
#include "lookup/register.h"
#include "utils/common.h"

std::string parseUType(const inst::structThing& inst, const std::string& str) {
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
    bin |= (0x000fffff & (imm)) << 12;

    return iUtils::intToString(bin);
}
