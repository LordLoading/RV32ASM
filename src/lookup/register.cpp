#include <format>
#include <stdexcept>
#include <cstdlib>
#include <vector>

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
            const int num = std::atoi(numStr.c_str());
            if (num < 0 || num > 31) throw std::invalid_argument("invalid register index");
            return num;
        } else {
            // Parse named register like "a0", "s1", etc.
            for (size_t i = 0; i < lookup.size(); i++) {
                if (lookup[i] == str) return static_cast<int>(i);
            }
            throw std::invalid_argument(std::format("invalid register name: {}", str));
        }
    }

} // namespace regs
