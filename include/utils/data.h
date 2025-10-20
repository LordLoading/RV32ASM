//
// Created by lor on 8/13/25.
//

#ifndef DUTILS_H
#define DUTILS_H

#pragma once

#include <string>
#include <vector>

#include "types/label_section.h"

namespace dUtils {

    int parseFloat(const std::string& numStr);
    int parseBin(const std::string& numStr);
    int parseHex(const std::string& numStr);
    int parseDec(const std::string& numStr);
    int parseLabel(const std::string& labelName, const std::vector<LabelSection>& labels);

    // Parses a string automatically detecting type (float, dec, hex, bin, label)
    int parseAuto(const std::string& numStr, const std::vector<LabelSection>& labels);
    int parseAuto(const std::string& numStr);

} // namespace dUtils

#endif // DUTILS_H
