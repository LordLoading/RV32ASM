//
// Created by lor on 8/25/25.
//

#ifndef PSEUDO_H
#define PSEUDO_H

#include <string>
#include <vector>

namespace pseudo {
    struct structThing {
        std::string name;
        int length;

    };

    std::vector<structThing> lookup = {
        {"li", 8},
        {"j", 4},
        {"mv", 4},
        {"not", 4},
        {"neg", 4},
        {"jr", 4},
        {"nop", 4},
        {"ret", 4},
        {"call", 12},
        {"pushb", 8},
        {"popb", 8},
        {"pushh", 8},
        {"poph", 8},
        {"pushw", 8},
        {"popw", 8},
        {"pushframe", 12},
        {"popframe", 12}

    };
}

#endif //PSEUDO_H
