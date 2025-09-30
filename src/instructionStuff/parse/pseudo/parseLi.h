//
// Created by lor on 8/26/25.
//

#ifndef PARSELI_H
#define PARSELI_H

#include <string>
#include <vector>

#include "../../../dUtils.h"
#include "../../assembleInst.h"

std::string parseLi(std::string str, std::vector<LabelSection> labels) {
    std::vector<std::string> tokens = iUtils::getParamsFromLine(str);

    const int num = dUtils::parseAuto(tokens[1], labels);

    const int lower = num & 0x0fff;
    int upper = (num >> 12) & 0x0fffff;

    if ((lower >> 11) == 1) upper++;

    std::string upperInst = "lui " + tokens[0] + ", " + std::to_string(upper);
    std::string lowerInst = "addi " + tokens[0] + ", " + tokens[0] + ", " + std::to_string(lower);

    return assembleInst(upperInst, labels) + assembleInst(lowerInst, labels);
};

#endif //PARSELI_H
