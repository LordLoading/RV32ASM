//
// Created by lor on 8/14/25.
//

#ifndef UTILS_H
#define UTILS_H

#pragma once

#include <string>
#include <vector>

#include "instructionParsers/iUtils.h"

namespace utils {
    std::string getFirstWord(std::string str) {
        int start = str.find_first_not_of("\t ");
        str = str.substr(start, str.size());
        return str.substr(0, str.find_first_of("\t "));
    }

    bool isInstruction(const std::string& str) {
        bool found = false;
        for (const iUtils::instruction& inst : iUtils::instructions) {
            if (inst.name == getFirstWord(str)) {
                found = true;
                break;
            }
        }

        return found;
    };

    int getLineSize(std::string line) {
        if (getFirstWord(line) == ".byte") return 1;
        if (getFirstWord(line) == ".half") return 2;
        if (getFirstWord(line) == ".word") return 4;
        if (getFirstWord(line) == ".string") {
            int firstChar = line.find_first_of("\"");
            int secondChar = line.find("\"", firstChar + 1);
            return secondChar - firstChar;
        }

        if (isInstruction(line)) return 4;

        return 0;
    }
}

#endif //UTILS_H
