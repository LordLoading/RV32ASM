//
// Created by lor on 8/21/25.
//

#include "parser/instruction/s_type.h"
#include <sstream>
#include <string>
#include <vector>

#include "lookup/register.h"
#include "utils/common.h"
#include "utils/data.h"
#include "utils/instruction.h"

std::string parseSType(const inst::structThing& inst, const std::string& str, const std::vector<LabelSection>& labels) {
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
