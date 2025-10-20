//
// Created by lor on 8/21/25.
//

#ifndef PARSESTYPE_H
#define PARSESTYPE_H
#include <string>
#include <vector>

#include "lookup/instruction.h"

class LabelSection;

std::string parseSType(const inst::structThing& inst, const std::string& str, const std::vector<LabelSection>& labels);

#endif
