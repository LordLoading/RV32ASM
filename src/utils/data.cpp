#include <regex>
#include <stdexcept>
#include <cstring>
#include <format>

#include "types/label_section.h"
#include "utils/common.h"

namespace dUtils {

    int parseFloat(const std::string& numStr) {
        const float num = std::stof(numStr);
        int numInt;
        std::memcpy(&numInt, &num, sizeof(int));
        return numInt;
    }

    int parseBin(const std::string& numStr) {
        const std::string data = numStr.substr(2);
        const long l = std::stol(data, nullptr, 2);
        int i;
        std::memcpy(&i, &l, sizeof(int));
        return i;
    }

    int parseHex(const std::string& numStr) {
        const std::string data = numStr.substr(2);
        const long l = std::stol(data, nullptr, 16);
        int i;
        std::memcpy(&i, &l, sizeof(int));
        return i;
    }

    int parseDec(const std::string& numStr) {
        const long l = std::stol(numStr, nullptr, 10);
        int i;
        std::memcpy(&i, &l, sizeof(int));
        return i;
    }

    int parseLabel(const std::string& labelName, const std::vector<LabelSection>& labels) {
        for (const auto& label : labels) {
            if (label.name == labelName) return label.address;
        }
        throw std::invalid_argument(std::format("Invalid label name: {}", labelName));
    }

    int parseAuto(const std::string& numStr, const std::vector<LabelSection>& labels) {
        std::string token = utils::getFirstWord(numStr);

        if (std::regex_match(token, std::regex("-?[0-9]+")))           return parseDec(token);
        if (std::regex_match(token, std::regex("-?[0-9]+\\.[0-9]+")))  return parseFloat(token);
        if (std::regex_match(token, std::regex("0x[0-9a-fA-F]+")))     return parseHex(token);
        if (std::regex_match(token, std::regex("0b[0-1]+")))           return parseBin(token);
        if (std::regex_match(token, std::regex("[0-9a-zA-Z]+")))       return parseLabel(token, labels);

        throw std::invalid_argument(std::format("Invalid constant '{}'", token));
    }

    int parseAuto(const std::string& numStr) {
        return parseAuto(numStr, std::vector<LabelSection>());
    }

} // namespace dUtils
