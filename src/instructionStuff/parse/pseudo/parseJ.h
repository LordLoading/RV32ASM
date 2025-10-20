//
// Created by loading on 30.08.2025.
//

#ifndef PARSEJ_H
#define PARSEJ_H
#include "../../assembleInst.h"

std::string parseJ(std::string line) {
    std::vector<std::string> tokens = iUtils::getParamsFromLine(line);

    return "jal ", "x0, " + tokens[0] + "\n";
}

#endif //PARSEJ_H
