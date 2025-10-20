//
// Created by lor on 8/26/25.
//

#include "parser/pseudo/li.h"

#include <string>
#include <vector>
#include <iostream>

#include "assembler/instruction.h"
#include "utils/data.h"
#include "utils/instruction.h"

std::string parseLi(const std::string& str, const std::vector<LabelSection>& labels) {
    std::vector<std::string> tokens = iUtils::getParamsFromLine(str);

    const int num = dUtils::parseAuto(tokens[1], labels);

    const int lower = num & 0x0fff;
    int upper = (num >> 12) & 0x0fffff;

    std::cout << tokens[1] << ": " << num;
    std::cout << ", lower: " << lower;

    if ((lower >> 11) == 1) upper++;

    std::string upperInst = "lui " + tokens[0] + ", " + std::to_string(upper);
    std::string lowerInst = "addi " + tokens[0] + ", " + tokens[0] + ", " + std::to_string(lower);

    std::cout << ", lowerInst: " << lowerInst << std::endl;

    return assembleInst(upperInst, labels) + assembleInst(lowerInst, labels);
}
