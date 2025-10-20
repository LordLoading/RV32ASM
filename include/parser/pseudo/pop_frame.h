//
// Created by lor on 10/7/25.
//

#ifndef PARSEPOPFRAME_H
#define PARSEPOPFRAME_H
#include <string>
#include <vector>
#include "types/label_section.h"

std::string parsePopFrame(const std::string& line, const std::vector<LabelSection>& labels);

#endif //PARSEPOPFRAME_H
