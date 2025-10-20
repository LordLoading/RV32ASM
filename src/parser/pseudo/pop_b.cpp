//
// Created by lor on 10/7/25.
//

#include "parser/pseudo/pop_b.h"
#include <string>
#include <vector>

#include "assembler/instruction.h"
#include "utils/instruction.h"

std::string parsePopB(const std::string& line, const std::vector<LabelSection>& labels) {
    std::vector<std::string> tokens = iUtils::getParamsFromLine(line);
    std::string moveSp = "addi sp, sp, 1";
    std::string store = "lb " + tokens[0] + ", 0(sp)";
    return assembleInst(moveSp, labels) + assembleInst(store, labels);
}
