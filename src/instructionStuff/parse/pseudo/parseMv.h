//
// Created by loading on 30.08.2025.
//

#ifndef PARSEMV_H
#define PARSEMV_H
#include <string>
#include <vector>

#include "../../assembleInst.h"
#include "../../iUtils.h"

std::string parseMv(std::string line) {
    std::vector<std::string> tokens = iUtils::getParamsFromLine(line);

    return "addi " + tokens[0] + ", x0, " + tokens[1] + "\n";
}

#endif //PARSEMV_H
