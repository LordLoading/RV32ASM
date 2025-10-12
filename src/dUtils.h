//
// Created by lor on 8/13/25.
//

#ifndef DUTILS_H
#define DUTILS_H

#pragma once

#include <cstring>
#include <format>
#include <regex>
#include <string>
#include <vector>

#include "LabelSection.h"

namespace dUtils {
    int parseFloat(std::string numStr) {
        float num = std::stof(numStr);
        int num2;
        std::memcpy(&num2, &num, sizeof(int));
        return num2;
    }

    int parseBin(std::string numStr) {
        std::string data = numStr.substr(2);
        long l = stol(data, nullptr, 2);
        int i;
        memcpy(&i, &l, sizeof(int));
        return i;
    }

    int parseHex(std::string numStr) {
        std::string data = numStr.substr(2);
        long l = stol(data, nullptr, 16);
        int i;
        memcpy(&i, &l, sizeof(int));
        return i;
    }

    int parseDec(std::string numStr) {
        long l = stol(numStr, nullptr, 10);
        int i;
        memcpy(&i, &l, sizeof(int));
        return i;
    }

    int parseLabel(std::string labelName, std::vector<LabelSection> labels) {
        for (LabelSection label : labels) {
            if (label.name == labelName) return label.address;
        }
        throw std::invalid_argument(std::format("Invalid label name: {}", labelName));
    }

    int parseAuto(std::string numStr, std::vector<LabelSection> labels) {
        numStr = utils::getFirstWord(numStr);
        if (std::regex_match(numStr, std::regex("-?[0-9]+")))           return parseDec(numStr);
        if (std::regex_match(numStr, std::regex("-?[0-9]+\\.[0-9]+")))  return parseFloat(numStr);
        if (std::regex_match(numStr, std::regex("0x[0-9a-fA-F]+")))     return parseHex(numStr);
        if (std::regex_match(numStr, std::regex("0b[0-1]+")))           return parseBin(numStr);
        if (std::regex_match(numStr, std::regex("[0-9a-zA-Z]+")))       return parseLabel(numStr, labels);
        else throw std::invalid_argument(std::format("Invalid constant '{}'", numStr));
    }

    int parseAuto(std::string numStr) {
        return parseAuto(numStr, std::vector<LabelSection>());
    }
} // DataParser

#endif //DATAPARSER_H
