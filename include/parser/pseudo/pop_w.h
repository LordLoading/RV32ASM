//
// Created by lor on 10/7/25.
//

#ifndef PARSEPOPW_H
#define PARSEPOPW_H
#include <string>
#include <vector>

class LabelSection;

std::string parsePopW(const std::string& line, const std::vector<LabelSection>& labels);

#endif //PARSEPOPW_H
