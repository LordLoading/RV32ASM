//
// Created by loading on 30.08.2025.
//

#include "parser/pseudo/mv.h"
#include <string>
#include <vector>
#include <format>

#include "assembler/instruction.h"
#include "utils/instruction.h"

std::string parseMv(const std::string& line, const std::vector<LabelSection>& labels) {
    std::vector<std::string> tokens = iUtils::getParamsFromLine(line);

    return assembleInst(std::format("addi ", tokens[0], ", x0, ", tokens[1]), labels);
}
