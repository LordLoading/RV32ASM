//
// Created by lor on 10/7/25.
//

#ifndef PARSEPUSHW_H
#define PARSEPUSHW_H
#include <string>
#include <vector>

class LabelSection;

std::string parsePushW(const std::string& line, const std::vector<LabelSection>& labels);

#endif //PARSEPUSHW_H
