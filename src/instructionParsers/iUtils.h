//
// Created by loading on 17.08.2025.
//

#ifndef INSTRUCTIONUTILS_H
#define INSTRUCTIONUTILS_H

#pragma once
#include "../utils.h"
#include "../lookup/inst.h"


namespace iUtils {
    std::string intToString(int bin) {
        std::cout << std::hex << bin << std::endl;
        std::string str = "";
        for (int i = 0; i < 4; ++i) {
            int masked = (bin >> (i * 8)) & 0xff;
            std::stringstream stream;
            stream << std::hex << masked;
            str += stream.str() + " ";
        }

        return str;
    }

    bool isInstruction(const std::string& str) {
        bool found = false;
        for (const inst::structThing& inst : inst::lookup) {
            if (inst.name == utils::getFirstWord(str)) {
                found = true;
                break;
            }
        }

        return found;
    };

    int getLineSize(std::string line) {
        if (utils::getFirstWord(line) == ".byte") return 1;
        if (utils::getFirstWord(line) == ".half") return 2;
        if (utils::getFirstWord(line) == ".word") return 4;
        if (utils::getFirstWord(line) == ".string") {
            int firstChar = line.find_first_of("\"");
            int secondChar = line.find("\"", firstChar + 1);
            return secondChar - firstChar;
        }

        if (isInstruction(line)) return 4;

        return 0;
    }

    struct offset {
        std::string data;
        std::string reg;
    };

    offset parseOffset (std::string str) {
        offset off;

        str = utils::getFirstWord(str);

        off.data = str.substr(0, str.find_first_of("("));
        off.reg = str.substr(str.find_first_of("(") + 1, str.find_first_of(")") - str.find_first_of("(") - 1);

        return off;
    }
}

#endif //INSTRUCTIONUTILS_H
