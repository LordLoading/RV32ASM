//
// Created by loading on 17.08.2025.
//

#ifndef INSTRUCTIONUTILS_H
#define INSTRUCTIONUTILS_H

#include <string>
#include <vector>
#include "lookup/instruction.h"

namespace iUtils {

    std::vector<std::string> getParamsFromLine(const std::string& line);

    std::string intToString(int bin, int bytes);
    std::string intToString(int bin);

    bool isInstruction(const std::string& str);

    int getPseudoSize(const std::string& line);

    int getLineSize(const std::string& line);

    struct offset {
        std::string data;
        std::string reg;
    };

    offset splitOffset(const std::string& str);

} // namespace iUtils

#endif // INSTRUCTIONUTILS_H
