//
// Created by loading on 17.08.2025.
//

#ifndef PARSEIALUTYPE_H
#define PARSEIALUTYPE_H
#include <string>
#include <vector>

#include "lookup/instruction.h"

class LabelSection;

std::string parseIALUType(const inst::structThing& inst, const std::string& str, const std::vector<LabelSection>& labels);

#endif
