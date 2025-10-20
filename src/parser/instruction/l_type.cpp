//
// Created by loading on 19.08.2025.
//

#include "parser/instruction/l_type.h"

#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "utils/instruction.h"
#include "utils/data.h"
#include "utils/common.h"
#include "lookup/register.h"

std::string parseLType(const inst::structThing& inst, const std::string& str, const std::vector<LabelSection>& labels) {
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
    bin |= (0x1f & regs::parse(tokens[0])) << 7;
    bin |= (0x7 & inst.funct3) << (12);
    iUtils::offset offset = iUtils::splitOffset(tokens[1]);
    bin |= (0x1f & regs::parse(offset.reg)) << (15);
    bin |= (0xfff & dUtils::parseAuto(offset.data, labels)) << (20);

    return iUtils::intToString(bin);
}
