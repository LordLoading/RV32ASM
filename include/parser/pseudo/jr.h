//
// Created by loading on 30.08.2025.
//

#ifndef PARSEJR_H
#define PARSEJR_H

#include <string>
#include <vector>

class LabelSection;

std::string parseJr(const std::string& line, const std::vector<LabelSection>& labels);

#endif //PARSEJR_H
