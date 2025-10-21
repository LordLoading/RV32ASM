#include "assembler/pseudo.h"
#include "lookup/pseudo.h"

namespace pseudo {

    const std::vector<structThing> lookup = {
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

} // namespace pseudo
