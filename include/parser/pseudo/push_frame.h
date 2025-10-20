//
// Created by lor on 10/7/25.
//

#ifndef PARSEPUSHFRAME_H
#define PARSEPUSHFRAME_H
#include <string>
#include <vector>
#include "types/label_section.h"

std::string parsePushFrame(const std::string& line, const std::vector<LabelSection>& labels);

#endif //PARSEPUSHFRAME_H
