//
// Created by lor on 8/13/25.
//

#ifndef LABELSECTION_H
#define LABELSECTION_H

#pragma once

#include <string>
#include <vector>
#include "utils/instruction.h"

class LabelSection {
public:
    std::string name;
    std::vector<std::string> lines;
    std::string data;
    int dataSize = 0;
    int address = 0;

    LabelSection() = default;
    explicit LabelSection(const std::string& name);

    int calculateSize();
    [[nodiscard]] bool isText() const;
};

#endif // LABELSECTION_H
