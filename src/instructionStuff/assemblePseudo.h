//
// Created by loading on 30.08.2025.
//

#ifndef ASSEMBLEPSEUDO_H
#define ASSEMBLEPSEUDO_H
#include <string>
#include <vector>

#include "../LabelSection.h"
#include "parse/pseudo/parseCall.h"
#include "parse/pseudo/parseJ.h"
#include "parse/pseudo/parseJr.h"
#include "parse/pseudo/parseLi.h"
#include "parse/pseudo/parseMv.h"
#include "parse/pseudo/parseNeg.h"
#include "parse/pseudo/parseNop.h"
#include "parse/pseudo/parseNot.h"
#include "parse/pseudo/parseRet.h"

std::string assemblePseudo(std::string line, std::vector<LabelSection> labels) {
    std::string fw = utils::getFirstWord(line);

    if (fw == "li") return parseLi(line, labels);
    else if (fw == "mv") return parseMv(line, labels);
    else if (fw == "not") return parseNot(line, labels);
    else if (fw == "nop") return parseNop(line, labels);
    else if (fw == "neg") return parseNeg(line, labels);
    else if (fw == "call") return parseCall(line, labels);
    else if (fw == "ret") return parseRet(line, labels);
    else if (fw == "j") return parseJ(line, labels);
    else if (fw == "jr") return parseJr(line, labels);
    else return "";
}

#endif //ASSEMBLEPSEUDO_H
