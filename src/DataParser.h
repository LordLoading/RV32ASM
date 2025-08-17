//
// Created by lor on 8/13/25.
//

#ifndef DATAPARSER_H
#define DATAPARSER_H

#pragma once

#include <bitset>
#include <cstring>
#include <regex>
#include <string>
#include <vector>

#include "LabelSection.h"

namespace DataParser {
    int parseFloat(std::string numStr) {
        float num = std::stof(numStr);
        int num2;
        std::memcpy(&num2, &num, sizeof(int));
        return num2;
    }

    int parseBin(std::string numStr) {
        std::string data = numStr.substr(2);
        return std::stoi(data, nullptr, 2);
    }

    int parseHex(std::string numStr) {
        std::string data = numStr.substr(2);
        return std::stoi(data, nullptr, 16);
    }

    int parseDec(std::string numStr) {
        std::string data = numStr.substr(2);
        return std::stoi(data, nullptr, 10);
    }

    int parseLabel(std::string labelName, std::vector<LabelSection> labels) {
        for (LabelSection label : labels) {
            if (label.name == labelName) return label.address;
        }
        throw std::invalid_argument("Invalid label name");
    }

    int parseAuto(std::string numStr, std::vector<LabelSection> labels) {
        if (std::regex_match(numStr, std::regex("[0-9]+")))         return parseDec(numStr);
        if (std::regex_match(numStr, std::regex("[0-9]+.[0-9]+")))  return parseFloat(numStr);
        if (std::regex_match(numStr, std::regex("0x[0-9a-fA-F]+"))) return parseHex(numStr);
        if (std::regex_match(numStr, std::regex("0b[0-1]+")))       return parseBin(numStr);
        if (std::regex_match(numStr, std::regex("[0-9a-zA-Z]+")))   return parseLabel(numStr, labels);
        else throw std::invalid_argument("Invalid constant");
    }

    int parseAuto(std::string numStr) {
        parseAuto(numStr, std::vector<LabelSection>());
    }
} // DataParser

#endif //DATAPARSER_H
