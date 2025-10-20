//
// Created by lor on 10/7/25.
//

#include "parser/pseudo/pop_frame.h"
#include <string>
#include <vector>

#include "parser/pseudo/mv.h"
#include "parser/pseudo/pop_w.h"

std::string parsePopFrame(const std::string& line, const std::vector<LabelSection>& labels) {
    std::string setsp = "mv fp, sp";
    std::string popFp = "popw fp";
    return parsePopW(popFp, labels) + parseMv(setsp, labels);
}
