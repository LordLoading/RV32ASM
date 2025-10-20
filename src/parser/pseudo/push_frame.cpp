//
// Created by lor on 10/7/25.
//

#include "parser/pseudo/push_frame.h"
#include <string>
#include <vector>

#include "parser/pseudo/mv.h"
#include "parser/pseudo/push_w.h"
#include "utils/instruction.h"

std::string parsePushFrame(const std::string& line, const std::vector<LabelSection>& labels) {
    std::vector<std::string> tokens = iUtils::getParamsFromLine(line);

    std::string pushFp = "pushw fp";
    std::string setFp = "mv fp, sp";
    return parsePushW(pushFp, labels) + parseMv(setFp, labels);
}
