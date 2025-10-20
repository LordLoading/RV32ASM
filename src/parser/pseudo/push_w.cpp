//
// Created by lor on 10/7/25.
//

#include "parser/pseudo/push_w.h"
#include <string>
#include <vector>

#include "assembler/instruction.h"
#include "utils/instruction.h"

std::string parsePushW(const std::string& line, const std::vector<LabelSection>& labels) {
    std::vector<std::string> tokens = iUtils::getParamsFromLine(line);
    std::string store = "sw " + tokens[0] + ", 0(sp)";
    std::string moveSp = "addi sp, sp, -4";
    return assembleInst(store, labels) + assembleInst(moveSp, labels);
}
