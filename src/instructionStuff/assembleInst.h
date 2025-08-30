//
// Created by loading on 30.08.2025.
//

#ifndef ASSEMBLEINST_H
#define ASSEMBLEINST_H
#pragma once

#include <string>
#include "iUtils.h"
#include "parse/parseBType.h"
#include "parse/parseEnvType.h"
#include "parse/parseIALUType.h"
#include "parse/parseJType.h"
#include "parse/parseLType.h"
#include "parse/parseRALUType.h"
#include "parse/parseSType.h"
#include "parse/parseUType.h"

std::string assembleInst(std::string line, std::vector<LabelSection> labels) {
    inst::structThing inst;
    for (const inst::structThing &i: inst::lookup) {
        if (utils::getFirstWord(line) == i.name) {
            inst = i;
            break;
        }
    }

    if (inst.name.empty()) return "";

    if (inst.fmt == "ralu") return parseRALUType(inst, line);
    else if (inst.fmt == "ialu") return parseIALUType(inst, line, labels);
    else if (inst.fmt == "l") return parseLType(inst, line, labels);
    else if (inst.fmt == "s") return parseSType(inst, line, labels);
    else if (inst.fmt == "b") return parseBType(inst, line);
    else if (inst.fmt == "j") return parseJType(inst, line);
    else if (inst.fmt == "u") return parseUType(inst, line);
    else if (inst.fmt == "env") return parseEnvType(inst);
}

#endif
