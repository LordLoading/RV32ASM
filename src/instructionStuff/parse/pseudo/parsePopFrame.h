//
// Created by lor on 10/7/25.
//

#ifndef PARSEPOPFRAME_H
#define PARSEPOPFRAME_H
#include <string>
#include <vector>

#include "../../assembleInst.h"
#include "../../assembleLine.h"

std::string parsePopFrame(std::string line, std::vector<LabelSection> labels) {
    std::string setsp = "mv fp, sp";
    std::string popFp = "popw fp";
    return parsePushW(pushFp, labels) + parseMv(setFp, labels);
}
#endif //PARSEPOPFRAME_H
