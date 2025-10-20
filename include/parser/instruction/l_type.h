//
// Created by loading on 19.08.2025.
//

#ifndef PARSELTYPE_H
#define PARSELTYPE_H

#include <string>
#include <vector>

#include "lookup/instruction.h"

class LabelSection;

std::string parseLType(const inst::structThing& inst, const std::string& str, const std::vector<LabelSection>& labels);

#endif
