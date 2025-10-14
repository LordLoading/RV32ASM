//
// Created by lor on 10/7/25.
//

#ifndef PARSEPOPB_H
#define PARSEPOPB_H
#include <string>
#include <vector>

#include "../../assembleInst.h"
#include "../../assembleLine.h"

std::string parsePopB(std::string line, std::vector<LabelSection> labels) {
    std::vector<std::string> tokens = iUtils::getParamsFromLine(line);
    std::string moveSp = "addi sp, sp, 1";
    std::string store = "lb " + tokens[0] + ", 0(sp)";
    return assembleInst(moveSp, labels) + assembleInst(store, labels);
}
#endif //PARSEPOPB_H
