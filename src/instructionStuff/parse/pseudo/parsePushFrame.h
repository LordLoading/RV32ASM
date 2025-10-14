//
// Created by lor on 10/7/25.
//

#ifndef PARSEPUSHFRAME_H
#define PARSEPUSHFRAME_H
#include <string>
#include <vector>

#include "../../assembleInst.h"
#include "../../assembleLine.h"

std::string parsePushFrame(std::string line, std::vector<LabelSection> labels) {
    std::vector<std::string> tokens = iUtils::getParamsFromLine(line);

    std::string pushFp = "pushw fp";
    std::string setFp = "mv fp, sp";
    return parsePushW(pushFp, labels) + parseMv(setFp, labels);
}
#endif //PARSEPUSHFRAME_H
