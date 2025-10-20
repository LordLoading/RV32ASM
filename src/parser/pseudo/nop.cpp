//
// Created by lor on 9/3/25.
//

#include "parser/pseudo/nop.h"
#include <string>
#include <vector>
#include "assembler/instruction.h"

std::string parseNop(const std::string& str, const std::vector<LabelSection>& labels) {
    return assembleInst("addi x0, x0, 0", labels);
}
