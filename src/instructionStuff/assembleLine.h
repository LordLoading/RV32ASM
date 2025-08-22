//
// Created by lor on 8/20/25.
//
#ifndef ASSEMBLELINE_H
#define ASSEMBLELINE_H

#pragma once

#include <string>

#include "parse/parseIALUType.h"
#include "parse/parseBType.h"
#include "parse/parseRALUType.h"
#include "parse/parseSType.h"
#include "parse/parseLType.h"

#include "../utils.h"
#include "../lookup/inst.h"
#include "parse/parseEnvType.h"
#include "parse/parseJType.h"
#include "parse/parseUType.h"

std::string assembleLine(std::string line, std::vector<LabelSection> labels) {
    inst::structThing inst;
    for (const inst::structThing &i: inst::lookup) {
        if (utils::getFirstWord(line) == i.name) {
            inst = i;
            break;
        }
    }

    std::string fw = utils::getFirstWord(line);

    if (inst.fmt == "ralu") return parseRALUType(inst, line);
    else if (inst.fmt == "ialu") return parseIALUType(inst, line, labels);
    else if (inst.fmt == "l") return parseLType(inst, line, labels);
    else if (inst.fmt == "s") return parseSType(inst, line, labels);
    else if (inst.fmt == "b") return parseBType(inst, line);
    else if (inst.fmt == "j") return parseJType(inst, line);
    else if (inst.fmt == "u") return parseUType(inst, line);
    else if (inst.fmt == "env") return parseEnvType(inst);
    else {
        line.erase(0 ,line.find_first_not_of("   "));
        line.erase(0, line.find(' '));
        if (fw == ".word") {
            line.erase(0, line.find(' '));
            int val = dUtils::parseAuto(line, labels);
            return iUtils::intToString(val, 4);
        } else if (fw == ".half") {
            line.erase(0, line.find(' '));
            int val = dUtils::parseAuto(line, labels);
            return iUtils::intToString(val, 2);
        } else if (fw == ".byte") {
            line.erase(0, line.find(' '));
            int val = dUtils::parseAuto(line, labels);
            return iUtils::intToString(val, 1);
        } else if (fw == ".string") {
            return "im slowly losing my sanity";
        }
    }
}

#endif
