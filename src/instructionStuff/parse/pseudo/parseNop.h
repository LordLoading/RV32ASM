//
// Created by lor on 9/3/25.
//

#ifndef PARSENOP_H
#define PARSENOP_H
#include <string>

#include "../../assembleInst.h"
#include "../../../LabelSection.h"

std::string parseNop(std::string str, std::vector<LabelSection> labels) {
    return assembleInst("addi x0, x0, 0");
}

#endif //PARSENOP_H
