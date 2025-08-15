//
// Created by lor on 8/13/25.
//

#ifndef LABELSECTION_H
#define LABELSECTION_H

#pragma once

#include <string>
#include <vector>

#include "Utils.h"

class LabelSection {
    public:
        std::string name;
        std::vector<std::string> lines;
        std::string data;
        int dataSize = 0;
        int address{};

        LabelSection() = default;
        explicit LabelSection(const std::string& name) {
            this->name = name;
        };

        int calculateSize() {
            for (const auto& currentLine : this->lines) {
                this->dataSize += Utils::getLineSize(currentLine);
            }

            return this->dataSize;
        }

        bool isText() {
            for (std::string currentLine : this->lines) {
                if (Utils::isInstruction(currentLine)) return true;
            }

            return false;
        }
};

#endif
