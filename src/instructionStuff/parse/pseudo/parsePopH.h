//
// Created by lor on 10/7/25.
//

#ifndef PARSEPOP_H
#define PARSEPOP_H
#include <string>
#include <vector>

#include "../../assembleInst.h"
#include "../../assembleLine.h"

std::string parsePopH(std::string line, std::vector<LabelSection> labels) {
    std::vector<std::string> tokens = iUtils::getParamsFromLine(line);
    std::string moveSp = "addi sp, sp, 2";
    std::string store = std::format("sb ", tokens[0], ", 0(sp)");
    return assembleLine(moveSp, labels) + assembleLine(store, labels);
}
#endif //PARSEPOP_H
