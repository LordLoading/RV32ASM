//
// Created by loading on 30.08.2025.
//

#ifndef PARSEJR_H
#define PARSEJR_H

#include "../../assembleInst.h"

std::string parseJr(std::string line) {
    std::vector<std::string> tokens = iUtils::getParamsFromLine(line);

    return "jalr x0, " + tokens[0] + "\n";
}

#endif //PARSEJR_H
