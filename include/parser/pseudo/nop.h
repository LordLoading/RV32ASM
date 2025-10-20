//
// Created by lor on 9/3/25.
//

#ifndef PARSENOP_H
#define PARSENOP_H
#include <string>
#include <vector>

class LabelSection;

std::string parseNop(const std::string& str, const std::vector<LabelSection>& labels);

#endif //PARSENOP_H
