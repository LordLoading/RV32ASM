//
// Created by loading on 19.08.2025.
//

#ifndef INST_H
#define INST_H

#include <string>
#include <vector>
#include <unordered_map>
#include <optional>

namespace inst {

    struct structThing {
        std::string name;
        std::string fmt;
        int opcode;
        int funct3;
        int funct7;
    };

    // Declare the global lookup vector (kept for backward compatibility)
    extern const std::vector<structThing> lookup;

    // Fast O(1) lookup map
    extern const std::unordered_map<std::string, structThing> lookupMap;

    // Fast lookup function using hash map
    std::optional<structThing> find(const std::string& name);

} // namespace inst

#endif // INST_H
