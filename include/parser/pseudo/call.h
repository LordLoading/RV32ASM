//
// Created by lor on 9/3/25.
//

#ifndef PARSECALL_H
#define PARSECALL_H
#include <string>
#include <vector>

class LabelSection;

std::string parseCall(const std::string& str, const std::vector<LabelSection>& labels);

#endif //PARSECALL_H
