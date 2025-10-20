//
// Created by lor on 8/20/25.
//

#ifndef ASSEMBLELINE_H
#define ASSEMBLELINE_H

#include <string>
#include <vector>
#include "types/label_section.h"

std::string assembleLine(const std::string& line, const std::vector<LabelSection>& labels);

#endif // ASSEMBLELINE_H
