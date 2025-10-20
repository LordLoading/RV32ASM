#include "../../include/utils/common.h"

namespace utils {

    std::string getFirstWord(const std::string& str) {
        // Find the first non-whitespace character
        const size_t start = str.find_first_not_of("\t ");
        if (start == std::string::npos)
            return "";  // No non-whitespace characters

        // Trim the leading whitespace
        std::string trimmed = str.substr(start);

        // Find the first space or tab after the first word
        const size_t end = trimmed.find_first_of("\t ");
        if (end == std::string::npos)
            return trimmed;  // Only one word

        return trimmed.substr(0, end);
    }

}
