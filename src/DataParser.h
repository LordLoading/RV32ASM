//
// Created by lor on 8/13/25.
//

#ifndef DATAPARSER_H
#define DATAPARSER_H
#include <bitset>
#include <cstring>
#include <string>

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

    int parseAuto(std::string numStr) {
        char numFormat = numStr[1];

        if (std::string::npos == numStr.find('.')) {
            return parseFloat(numStr);
        }

        switch (numFormat) {
            case "b":
                return parseBin(numStr);
            case "x":
                return parseHex(numStr);
            default:
                return parseDec(numStr);
        }
    }
} // DataParser

#endif //DATAPARSER_H
