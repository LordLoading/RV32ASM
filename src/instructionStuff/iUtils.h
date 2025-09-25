//
// Created by loading on 17.08.2025.
//

#ifndef INSTRUCTIONUTILS_H
#define INSTRUCTIONUTILS_H

#pragma once
#include "../utils.h"
#include "../lookup/inst.h"


namespace iUtils {
    std::vector<std::string> getParamsFromLine(std::string line) {
        line.erase(0 ,line.find_first_not_of("   "));
        line.erase(0, line.find(' '));

        std::stringstream strStream(line);
        std::string intermediate;
        std::vector<std::string> tokens;

        while (std::getline(strStream, intermediate, ',')) {
            tokens.push_back(utils::getFirstWord(intermediate));
        }

        return tokens;
    }

    std::string intToString(int bin, int bytes) {
        std::string str = "";
        for (int i = 0; i < bytes; ++i) {
            int masked = (bin >> (i * 8)) & 0xff;
            std::stringstream stream;
            stream << std::hex << masked;
            std::string byte = stream.str();
            while (byte.size() < 2) byte = "0" + byte;
            str += byte + " ";
        }

        return str;
    }

    std::string intToString(int bin) {
        return intToString(bin, 4);
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
        int elemSize = 0;
        if (utils::getFirstWord(line) == ".byte") elemSize = 1;
        if (utils::getFirstWord(line) == ".half") elemSize = 2;
        if (utils::getFirstWord(line) == ".word") elemSize = 4;
        if (utils::getFirstWord(line) == ".string") {
            int firstChar = line.find_first_of("\"");
            int secondChar = line.find("\"", firstChar + 1);
            return secondChar - firstChar + 1;
        }

        if (elemSize != 0) {
            return elemSize * getParamsFromLine(line).size();
        }

        if (isInstruction(line)) return 4;

        return 0;
    }

    struct offset {
        std::string data;
        std::string reg;
    };

    offset splitOffset (std::string str) {
        offset off;

        str = utils::getFirstWord(str);

        off.data = str.substr(0, str.find_first_of("("));
        off.reg = str.substr(str.find_first_of("(") + 1, str.find_first_of(")") - str.find_first_of("(") - 1);

        return off;
    }
}

#endif
