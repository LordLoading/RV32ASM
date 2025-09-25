//
// Created by lor on 8/20/25.
//
#ifndef ASSEMBLELINE_H
#define ASSEMBLELINE_H

#pragma once

#include <string>

#include "assembleInst.h"
#include "assemblePseudo.h"
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
    std::string fw = utils::getFirstWord(line);

    std::string data = assembleInst(line, labels);
    if (!data.empty()) return data;

    else data = assemblePseudo(line, labels);
    if (!data.empty()) return data;

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
            line.erase(0, line.find('"') + 1);
            line.erase(line.find_last_of('"'), line.size());
            std::string bytes = "";
            for (char c: line) {
                bytes += iUtils::intToString(c, 1);
            }
            bytes += "00 ";
            return bytes;
        } else {
            throw std::invalid_argument(std::format("Invalid instruction: {}", fw));
        }
    }
}

#endif
