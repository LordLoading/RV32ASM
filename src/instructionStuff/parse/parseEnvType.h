//
// Created by lor on 8/22/25.
//

#ifndef PARSEENVTYPE_H
#define PARSEENVTYPE_H
#include <string>

#include "../iUtils.h"

std::string parseEnvType(inst::structThing inst) {
    if (inst.name == "ecall") return  iUtils::intToString(0x00000073);
    else if (inst.name == "ebreak") return iUtils::intToString(0x00100073);
}

#endif
