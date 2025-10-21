#include <format>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cctype>

namespace regs {

    const std::vector<std::string> lookup = {
        "zero","ra","sp","gp","tp","t0","t1","t2","fp","s1",
        "a0","a1","a2","a3","a4","a5","a6","a7","s2","s3",
        "s4","s5","s6","s7","s8","s9","s10","s11","t3","t4","t5","t6"
    };

    int parse(const std::string& str) {
        if (str.empty()) throw std::invalid_argument("empty register string");

        if (str[0] == 'x') {
            // Parse numeric register "x0"-"x31"
            const std::string numStr = str.substr(1);

            // Validate that the string after 'x' contains only digits
            if (numStr.empty() || !std::all_of(numStr.begin(), numStr.end(), ::isdigit)) {
                throw std::invalid_argument(std::format("invalid register format: {}", str));
            }

            const int num = std::atoi(numStr.c_str());

            // Bounds check: RISC-V has exactly 32 registers (x0-x31)
            if (num < 0 || num > 31) {
                throw std::invalid_argument(std::format("register index out of bounds (0-31): x{}", num));
            }

            return num;
        } else {
            // Parse named register like "a0", "s1", etc.
            for (size_t i = 0; i < lookup.size(); i++) {
                if (lookup[i] == str) {
                    // Extra bounds check for safety (should always be within range)
                    if (i > 31) {
                        throw std::invalid_argument(std::format("internal error: register index exceeds 31: {}", i));
                    }
                    return static_cast<int>(i);
                }
            }
            throw std::invalid_argument(std::format("invalid register name: {}", str));
        }
    }

} // namespace regs
