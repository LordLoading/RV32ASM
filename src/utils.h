//
// Created by lor on 8/14/25.
//

#ifndef UTILS_H
#define UTILS_H

#pragma once

#include <string>

namespace utils {
    std::string getFirstWord(std::string str) {
        int start = str.find_first_not_of("\t ");
        str = str.substr(start, str.size());
        return str.substr(0, str.find_first_of("\t "));
    }
}

#endif
