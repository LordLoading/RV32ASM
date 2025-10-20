//
// Created by loading on 30.08.2025.
//

#ifndef PARSENEG_H
#define PARSENEG_H
#include <string>
#include <vector>

class LabelSection;

std::string parseNeg(const std::string& line, const std::vector<LabelSection>& labels);

#endif //PARSENEG_H
