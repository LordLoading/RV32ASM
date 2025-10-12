//
// Created by lor on 10/7/25.
//

#ifndef PARSEPOPH_H
#define PARSEPOPH_H
#include <string>
#include <vector>

#include "../../assembleInst.h"
#include "../../assembleLine.h"

std::string parsePopH(std::string line, std::vector<LabelSection> labels) {
    std::vector<std::string> tokens = iUtils::getParamsFromLine(line);
    std::string moveSp = "addi sp, sp, 2";
    std::string store = "sb " + tokens[0] + ", 0(sp)";
    return assembleInst(moveSp, labels) + assembleInst(store, labels);
}
#endif //PARSEPOP_H
