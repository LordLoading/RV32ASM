#include "utils/instruction.h"
#include <sstream>

#include "lookup/pseudo.h"
#include "utils/common.h"

namespace iUtils {

    std::vector<std::string> getParamsFromLine(const std::string& line) {
        std::string trimmed = line;
        trimmed.erase(0, trimmed.find_first_not_of(" \t"));
        trimmed.erase(0, trimmed.find(' '));

        std::stringstream strStream(trimmed);
        std::string intermediate;
        std::vector<std::string> tokens;

        while (std::getline(strStream, intermediate, ',')) {
            tokens.push_back(utils::getFirstWord(intermediate));
        }

        return tokens;
    }

    std::string intToString(const int bin, const int bytes) {
        std::string str;
        for (int i = 0; i < bytes; ++i) {
            const int masked = (bin >> (i * 8)) & 0xff;
            std::stringstream stream;
            stream << std::hex << masked;
            std::string byte = stream.str();
            while (byte.size() < 2) byte = "0" + byte;
            str += byte + " ";
        }
        return str;
    }

    std::string intToString(const int bin) {
        return intToString(bin, 4);
    }

    bool isInstruction(const std::string& str) {
        const std::string word = utils::getFirstWord(str);
        // Use fast O(1) hash map lookup instead of O(n) linear search
        return inst::find(word).has_value();
    }

    int getPseudoSize(const std::string& line) {
        const std::string word = utils::getFirstWord(line);
        for (const auto&[name, length] : pseudo::lookup) {
            if (name == word) return length;
        }
        return 0; // Return 0 if no pseudo instruction matched
    }

    int getLineSize(const std::string& line) {
        const std::string firstWord = utils::getFirstWord(line);
        int elemSize = 0;

        if (firstWord == ".byte") elemSize = 1;
        if (firstWord == ".half") elemSize = 2;
        if (firstWord == ".word") elemSize = 4;
        if (firstWord == ".string") {
            const size_t firstChar = line.find_first_of('\"');
            const size_t secondChar = line.find('\"', firstChar + 1);
            // Calculate string length between quotes, plus 1 for null terminator
            return static_cast<int>(secondChar - firstChar - 1 + 1);
        }

        if (elemSize != 0) {
            return elemSize * static_cast<int>(getParamsFromLine(line).size());
        }

        if (isInstruction(line)) return 4;

        return getPseudoSize(line);
    }

    offset splitOffset(const std::string& str) {
        offset off;
        const std::string word = utils::getFirstWord(str);

        const size_t open = word.find_first_of('(');
        const size_t close = word.find_first_of(')');

        off.data = word.substr(0, open);
        off.reg = word.substr(open + 1, close - open - 1);

        return off;
    }

} // namespace iUtils
