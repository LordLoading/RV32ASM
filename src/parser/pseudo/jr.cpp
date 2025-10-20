//
// Created by loading on 30.08.2025.
//

#include "parser/pseudo/jr.h"

#include <string>
#include <vector>
#include <format>

#include "assembler/instruction.h"
#include "utils/instruction.h"

std::string parseJr(const std::string& line, const std::vector<LabelSection>& labels) {
    std::vector<std::string> tokens = iUtils::getParamsFromLine(line);

    return assembleInst(std::format("jalr ", "x0, ", tokens[0]), labels);
}
