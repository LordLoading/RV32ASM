//
// Created by loading on 30.08.2025.
//

#ifndef ASSEMBLEINST_H
#define ASSEMBLEINST_H

#include <string>
#include <vector>
#include "types/label_section.h"

std::string assembleInst(const std::string& line, const std::vector<LabelSection>& labels);

#endif // ASSEMBLEINST_H
