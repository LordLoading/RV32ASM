//
// Created by lor on 10/7/25.
//

#ifndef PARSEPUSH_H
#define PARSEPUSH_H
#include <string>
#include <vector>

#include "../../assembleInst.h"
#include "../../assembleLine.h"

std::string parsePushH(std::string line, std::vector<LabelSection> labels) {
    std::vector<std::string> tokens = iUtils::getParamsFromLine(line);
    std::string store = std::format("sh ", tokens[0], ", 0(sp)");
    std::string moveSp = "addi sp, sp, -2";
    return assembleLine(store, labels) + assembleLine(moveSp, labels);
}
#endif //PARSEPUSH_H
