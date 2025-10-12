//
// Created by lor on 10/7/25.
//

#ifndef PARSEPUSHH_H
#define PARSEPUSHH_H
#include <string>
#include <vector>

#include "../../assembleInst.h"
#include "../../assembleLine.h"

std::string parsePushH(std::string line, std::vector<LabelSection> labels) {
    std::vector<std::string> tokens = iUtils::getParamsFromLine(line);
    std::string store = "sh " + tokens[0] + ", 0(sp)";
    std::string moveSp = "addi sp, sp, -2";
    return assembleInst(store, labels) + assembleInst(moveSp, labels);
}
#endif //PARSEPUSHH_H
