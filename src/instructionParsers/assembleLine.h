//
// Created by lor on 8/20/25.
//
#ifndef ASSEMBLELINE_H
#define ASSEMBLELINE_H

#pragma once

#include <string>

#include "parseIALUType.h"
#include "parseLType.h"
#include "parseRALUType.h"
#include "parseSType.h"
#include "../utils.h"
#include "../lookup/inst.h"

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
