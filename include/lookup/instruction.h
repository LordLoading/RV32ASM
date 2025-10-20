//
// Created by loading on 19.08.2025.
//

#ifndef INST_H
#define INST_H

#include <string>
#include <vector>

namespace inst {

    struct structThing {
        std::string name;
        std::string fmt;
        int opcode;
        int funct3;
        int funct7;
    };

    // Declare the global lookup vector
    extern const std::vector<structThing> lookup;

} // namespace inst

#endif // INST_H
