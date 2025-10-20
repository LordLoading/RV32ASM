//
// Created by lor on 10/7/25.
//

#ifndef PARSEPOPH_H
#define PARSEPOPH_H
#include <string>
#include <vector>

class LabelSection;

std::string parsePopH(const std::string& line, const std::vector<LabelSection>& labels);

#endif //PARSEPOPH_H
