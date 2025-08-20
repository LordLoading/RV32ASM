//
// Created by loading on 19.08.2025.
//

#ifndef REG_H
#define REG_H

namespace regs {
    std::vector<std::string> lookup = {
        "zero",
        "ra",
        "sp",
        "gp",
        "tp",
        "t0",
        "t1",
        "t2",
        "s0",
        "s1",
        "a0",
        "a1",
        "a2",
        "a3",
        "a4",
        "a5",
        "a6",
        "a7",
        "s2",
        "s3",
        "s4",
        "s5",
        "s6",
        "s7",
        "s8",
        "s9",
        "s10",
        "s11",
        "t3",
        "t4",
        "t5",
        "t6",
    };

    int parse(std::string str) {
        if (str[0] == 'x') {
            str.erase(0, 1);
            int num = atoi(str.c_str());
            if (num < 0 || num > 31) throw std::invalid_argument("invalid register index");
            else return num;
        } else {
            for (int i = 0; i < lookup.size(); i++) {
                if (lookup[i] == str) return i;
            }
            throw std::invalid_argument("invalid register name");
        }
    }
}
#endif //REG_H
