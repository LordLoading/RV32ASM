//
// Created by loading on 30.08.2025.
//

#ifndef PARSENOT_H
#define PARSENOT_H
#include <string>
#include <vector>

#include "../../assembleInst.h"

std::string parseNot(std::string line, std::vector<LabelSection> labels) {
    std::vector<std::string> tokens = iUtils::getParamsFromLine(line);

    return assembleInst(std::format("xori ", tokens[0], ", ", tokens[1], ", -1"), labels);
}

#endif //PARSENOT_H
