//
// Created by loading on 30.08.2025.
//

#ifndef PARSENEG_H
#define PARSENEG_H
#include <string>
#include <vector>

#include "../../assembleInst.h"

std::string parseNeg(std::string line) {
    std::vector<std::string> tokens = iUtils::getParamsFromLine(line);

    return "sub " + tokens[0] + ", x0, " + tokens[1] + "\n";
}

#endif //PARSENEG_H
