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
#include "parse/parseJType.h"

std::string assembleLine(std::string line, std::vector<LabelSection> labels) {
    inst::structThing inst;
    for (const inst::structThing &i: inst::lookup) {
        if (utils::getFirstWord(line) == i.name) {
            inst = i;
            break;
        }
    }


    if (inst.fmt == "ralu") return parseRALUType(inst, line);
    else if (inst.fmt == "ialu") return parseIALUType(inst, line, labels);
    else if (inst.fmt == "l") return parseLType(inst, line, labels);
    else if (inst.fmt == "s") return parseSType(inst, line, labels);
    else if (inst.fmt == "b") return parseBType(inst, line);
    else if (inst.fmt == "j") return parseJType(inst, line);
    else {
        if (utils::getFirstWord(line) == ".word") {
            line.erase(0, line.find(' '));
            int val = dUtils::parseAuto(line, labels);
            return iUtils::intToString(val, 4);
        } else if (utils::getFirstWord(line) == ".half") {
            line.erase(0, line.find(' '));
            int val = dUtils::parseAuto(line, labels);
            return iUtils::intToString(val, 2);
        } else if (utils::getFirstWord(line) == ".byte") {
            line.erase(0, line.find(' '));
            int val = dUtils::parseAuto(line, labels);
            return iUtils::intToString(val, 1);
        } else if (utils::getFirstWord(line) == ".string") {
            return "im slowly losing my sanity";
        }
    }
}

#endif
