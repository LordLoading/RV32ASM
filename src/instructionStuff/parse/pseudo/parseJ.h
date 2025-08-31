//
// Created by loading on 30.08.2025.
//

#ifndef PARSEJ_H
#define PARSEJ_H
#include "../../assembleInst.h"

std::string parseJ(std::string line, std::vector<LabelSection> labels) {
    std::vector<std::string> tokens = iUtils::getParamsFromLine(line);

    return assembleInst(std::format("jal ", "x0, ", tokens[0]), labels);
}

#endif //PARSEJ_H
