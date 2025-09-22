//
// Created by lor on 9/3/25.
//

#ifndef PARSECALL_H
#define PARSECALL_H
#include <string>
#include <vector>

#include "../../assembleInst.h"

std::string parseCall(std::string str, std::vector<LabelSection> labels) {
    std::vector<std::string> tokens = iUtils::getParamsFromLine(str);

    const int num = dUtils::parseAuto(tokens[1], labels);

    const int lower = num & 0x0fff;
    int upper = (num >> 12) & 0x0fffff;

    if ((lower >> 11) == 1) upper++;

    std::string lowerInst = std::format("addi ", tokens[0], ", x0, ", lower);
    std::string upperInst = std::format("lui ", tokens[0], ", ", upper);

    return assembleInst(upperInst, labels) + assembleInst(lowerInst, labels);
};

#endif //PARSECALL_H
