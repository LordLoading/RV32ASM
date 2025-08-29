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
        {"li", 8}
    };
}

#endif //PSEUDO_H
