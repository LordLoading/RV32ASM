//
// Created by loading on 30.08.2025.
//

#ifndef ASSEMBLEPSEUDO_H
#define ASSEMBLEPSEUDO_H

#include <string>
#include <vector>
#include "../types/label_section.h"

std::string assemblePseudo(const std::string& line, const std::vector<LabelSection>& labels);

#endif // ASSEMBLEPSEUDO_H
