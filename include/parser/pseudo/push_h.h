//
// Created by lor on 10/7/25.
//

#ifndef PARSEPUSHH_H
#define PARSEPUSHH_H
#include <string>
#include <vector>

class LabelSection;

std::string parsePushH(const std::string& line, const std::vector<LabelSection>& labels);

#endif //PARSEPUSHH_H
