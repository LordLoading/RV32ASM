//
// Created by lor on 10/7/25.
//

#ifndef PARSEPOPW_H
#define PARSEPOPW_H
#include <string>
#include <vector>

#include "../../assembleInst.h"
#include "../../assembleLine.h"

std::string parsePopW(std::string line, std::vector<LabelSection> labels) {
    std::vector<std::string> tokens = iUtils::getParamsFromLine(line);
    std::string moveSp = "addi sp, sp, 4";
    std::string store = "sb " + tokens[0] + ", 0(sp)";
    return assembleInst(moveSp, labels) + assembleInst(store, labels);
}
#endif //PARSEPOPW_H
