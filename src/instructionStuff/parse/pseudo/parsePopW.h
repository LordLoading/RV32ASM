//
// Created by lor on 10/7/25.
//

#ifndef PARSEPOP_W
#define PARSEPOP_W
#include <string>
#include <vector>

#include "../../assembleInst.h"
#include "../../assembleLine.h"

std::string parsePopW(std::string line, std::vector<LabelSection> labels) {
    std::vector<std::string> tokens = iUtils::getParamsFromLine(line);
    std::string moveSp = "addi sp, sp, 4";
    std::string store = std::format("sb ", tokens[0], ", 0(sp)");
    return assembleLine(moveSp, labels) + assembleLine(store, labels);
}
#endif //PARSEPOP_W
