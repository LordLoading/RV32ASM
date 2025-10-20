//
// Created by lor on 9/24/25.
//

#include "parser/pseudo/ret.h"
#include <string>
#include <vector>

#include "assembler/instruction.h"

std::string parseRet(const std::string& str, const std::vector<LabelSection>& labels) {
   return assembleInst("jalr x0, 0(ra)", labels);
}
