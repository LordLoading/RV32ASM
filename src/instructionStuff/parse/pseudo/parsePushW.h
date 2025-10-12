//
// Created by lor on 10/7/25.
//

#ifndef PARSEPUSHW_H
#define PARSEPUSHW_H
#include <string>
#include <vector>

#include "../../assembleInst.h"
#include "../../assembleLine.h"

std::string parsePushW(std::string line, std::vector<LabelSection> labels) {
    std::vector<std::string> tokens = iUtils::getParamsFromLine(line);
    std::string store = "sw " + tokens[0] + ", 0(sp)";
    std::string moveSp = "addi sp, sp, -4";
    return assembleInst(store, labels) + assembleInst(moveSp, labels);
}
#endif //PARSEPUSHW_H
