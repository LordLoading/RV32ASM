//
// Created by lor on 9/3/25.
//

#include <string>
#include <vector>

#include "assembler/instruction.h"
#include "types/label_section.h"
#include "utils/instruction.h"
#include "parser/pseudo/li.h"

std::string parseCall(const std::string& str, const std::vector<LabelSection>& labels) {
    const std::vector<std::string> tokens = iUtils::getParamsFromLine(str);

    //const int num = dUtils::parseAuto(tokens[1], labels);

    std::string li = parseLi("li ra, " + tokens[0], labels);
    std::string j = assembleInst("jalr ra, 0(ra)", labels);

    return li + j;
}
