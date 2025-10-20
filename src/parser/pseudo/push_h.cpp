//
// Created by lor on 10/7/25.
//

#include "parser/pseudo/push_h.h"
#include <string>
#include <vector>

#include "assembler/instruction.h"
#include "utils/instruction.h"

std::string parsePushH(const std::string& line, const std::vector<LabelSection>& labels) {
    std::vector<std::string> tokens = iUtils::getParamsFromLine(line);
    std::string store = "sh " + tokens[0] + ", 0(sp)";
    std::string moveSp = "addi sp, sp, -2";
    return assembleInst(store, labels) + assembleInst(moveSp, labels);
}
