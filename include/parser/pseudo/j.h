//
// Created by loading on 30.08.2025.
//

#ifndef PARSEJ_H
#define PARSEJ_H

#include <string>
#include <vector>

class LabelSection;

std::string parseJ(const std::string& line, const std::vector<LabelSection>& labels);

#endif //PARSEJ_H
