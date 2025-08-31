//
// Created by loading on 30.08.2025.
//

#ifndef PARSEJR_H
#define PARSEJR_H

#include "../../assembleInst.h"

std::string parseJr(std::string line, std::vector<LabelSection> labels) {
    std::vector<std::string> tokens = iUtils::getParamsFromLine(line);

    return assembleInst(std::format("jalr ", "x0, ", tokens[0]), labels);
}

#endif //PARSEJR_H
