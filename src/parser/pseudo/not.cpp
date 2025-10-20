//
// Created by loading on 30.08.2025.
//

#include "parser/pseudo/not.h"
#include <string>
#include <vector>
#include <format>

#include "assembler/instruction.h"
#include "utils/instruction.h"

std::string parseNot(const std::string& line, const std::vector<LabelSection>& labels) {
    std::vector<std::string> tokens = iUtils::getParamsFromLine(line);

    return assembleInst(std::format("xori ", tokens[0], ", ", tokens[1], ", -1"), labels);
}
