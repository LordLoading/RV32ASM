//
// Created by lor on 9/24/25.
//

#ifndef PARSERET_H
#define PARSERET_H
#include <string>
#include <vector>

#include "../../assembleInst.h"

class LabelSection;

std::string parseRet(std::string str, std::vector<LabelSection> labels) {
   return assembleInst("jalr x0, ra, 0", labels);
}
#endif //PARSERET_H
