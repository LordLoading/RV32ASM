#ifndef PARSEPUSHB_H
#define PARSEPUSHB_H
#include <string>
#include <vector>

#include "../../assembleInst.h"
#include "../../assembleLine.h"

std::string parsePushB(std::string line, std::vector<LabelSection> labels) {
    std::vector<std::string> tokens = iUtils::getParamsFromLine(line);
    std::string store = "sb " + tokens[0] + ", 0(sp)";
    std::string moveSp = "addi sp, sp, -1";
    return assembleInst(store, labels) + assembleInst(moveSp, labels);
}
#endif //PARSEPUSHB_H
