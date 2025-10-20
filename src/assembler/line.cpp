#include "assembler/line.h"
#include "assembler/instruction.h"
#include "assembler/pseudo.h"
#include "utils/common.h"
#include "utils/data.h"

#include <format>
#include <stdexcept>

std::string assembleLine(const std::string& line, const std::vector<LabelSection>& labels) {
    const std::string fw = utils::getFirstWord(line);

    std::string data = assembleInst(line, labels);
    if (!data.empty()) return data;

    data = assemblePseudo(line, labels);
    if (!data.empty()) return data;

    std::string trimmed = line;
    trimmed.erase(0, trimmed.find_first_not_of(" \t"));
    trimmed.erase(0, trimmed.find(' '));

    if (fw == ".word") {
        trimmed.erase(0, trimmed.find(' '));
        const int val = dUtils::parseAuto(trimmed, labels);
        return iUtils::intToString(val, 4);
    }
    if (fw == ".half") {
        trimmed.erase(0, trimmed.find(' '));
        const int val = dUtils::parseAuto(trimmed, labels);
        return iUtils::intToString(val, 2);
    }
    if (fw == ".byte") {
        trimmed.erase(0, trimmed.find(' '));
        const int val = dUtils::parseAuto(trimmed, labels);
        return iUtils::intToString(val, 1);
    }
    if (fw == ".string") {
        trimmed.erase(0, trimmed.find('"') + 1);
        trimmed.erase(trimmed.find_last_of('"'), trimmed.size());
        std::string bytes;
        for (const char c : trimmed) {
            bytes += iUtils::intToString(c, 1);
        }
        bytes += "00 ";
        return bytes;
    }
    throw std::invalid_argument(std::format("Invalid instruction: {}", fw));
}
