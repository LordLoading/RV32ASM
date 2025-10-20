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

std::string parseCall(std::string str) {
    std::vector<std::string> tokens = iUtils::getParamsFromLine(str);

    return "li ra, " + tokens[0] + "\n jalr ra, 0(ra) \n";
};

#endif //PARSECALL_H
