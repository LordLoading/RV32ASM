//
// Created by lor on 10/7/25.
//

#ifndef PARSEPUSH_H
#define PARSEPUSH_H
#include <string>
#include <vector>

#include "../../assembleInst.h"
#include "../../assembleLine.h"

std::string parsePushW(std::string line, std::vector<LabelSection> labels) {
    std::vector<std::string> tokens = iUtils::getParamsFromLine(line);
    std::string moveSp = "addi sp, sp, 1";
    std::string store = std::format("sb ", tokens[0], ", 0(sp)");
    return assembleLine(moveSp, labels) + assembleLine(store, labels);
}
#endif //PARSEPUSH_H
