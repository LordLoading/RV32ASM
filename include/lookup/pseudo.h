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

    // Declare the lookup vector
    extern const std::vector<structThing> lookup;

} // namespace pseudo

#endif // PSEUDO_H
