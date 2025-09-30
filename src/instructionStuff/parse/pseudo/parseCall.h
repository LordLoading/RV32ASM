//
// Created by lor on 9/3/25.
//

#ifndef PARSECALL_H
#define PARSECALL_H
#include <string>
#include <vector>

#include "parseJ.h"
#include "parseLi.h"
#include "../../assembleInst.h"

std::string parseCall(std::string str, std::vector<LabelSection> labels) {
    std::vector<std::string> tokens = iUtils::getParamsFromLine(str);

    //const int num = dUtils::parseAuto(tokens[1], labels);

    std::string li = parseLi("li ra, " + tokens[0], labels);
    std::string j = assembleInst("jalr ra, 0(ra)", labels);

    return li + j;
};

#endif //PARSECALL_H
