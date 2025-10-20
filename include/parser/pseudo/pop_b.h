//
// Created by lor on 10/7/25.
//

#ifndef PARSEPOPB_H
#define PARSEPOPB_H
#include <string>
#include <vector>

class LabelSection;

std::string parsePopB(const std::string& line, const std::vector<LabelSection>& labels);

#endif //PARSEPOPB_H
