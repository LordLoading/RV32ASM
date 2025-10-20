//
// Created by loading on 17.08.2025.
//

#include "parser/instruction/r_type.h"
#include <sstream>
#include <string>
#include <vector>

#include "utils/instruction.h"
#include "utils/common.h"
#include "lookup/register.h"

std::string parseRALUType(const inst::structThing& inst, const std::string& str) {
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

    bin |= (0x7f & inst.opcode);
    bin |= (0x1f & regs::parse(tokens[0])) << 7;
    bin |= (0x7 & inst.funct3) << (12);
    bin |= (0x1f & regs::parse(tokens[1])) << (15);
    bin |= (0x1f & regs::parse(tokens[2])) << (20);
    bin |= (0x7f & inst.funct7) << (25);

    return iUtils::intToString(bin);
}
