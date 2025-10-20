//
// Created by loading on 30.08.2025.
//

#ifndef PARSEMV_H
#define PARSEMV_H
#include <string>
#include <vector>

class LabelSection;

std::string parseMv(const std::string& line, const std::vector<LabelSection>& labels);

#endif //PARSEMV_H
