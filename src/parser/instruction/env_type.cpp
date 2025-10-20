//
// Created by lor on 8/22/25.
//

#include "parser/instruction/env_type.h"

#include <stdexcept>

#include "utils/instruction.h"

std::string parseEnvType(const inst::structThing& inst) {
    if (inst.name == "ecall") return  iUtils::intToString(0x00000073);
    if (inst.name == "ebreak") return iUtils::intToString(0x00100073);
    throw std::runtime_error("Invalid envType instruction");
}
