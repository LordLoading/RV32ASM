//
// Created by loading on 19.08.2025.
//

#ifndef REG_H
#define REG_H

#include <string>
#include <vector>

namespace regs {

    extern const std::vector<std::string> lookup;

    // Parses a register string ("x0" or "a0") into its index
    int parse(const std::string& str);

} // namespace regs

#endif // REG_H
