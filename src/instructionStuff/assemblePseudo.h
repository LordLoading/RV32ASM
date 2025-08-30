//
// Created by loading on 30.08.2025.
//

#ifndef ASSEMBLEPSEUDO_H
#define ASSEMBLEPSEUDO_H
#include <string>
#include <vector>

#include "../LabelSection.h"
#include "parse/pseudo/parseLi.h"
#include "parse/pseudo/parseMv.h"

std::string assemblePseudo(std::string line, std::vector<LabelSection> labels) {
    std::string fw = utils::getFirstWord(line);

    if (fw == "li") return parseLi(line, labels);
    else if (fw == "mv") return parseMv(line, labels);
}

#endif //ASSEMBLEPSEUDO_H
