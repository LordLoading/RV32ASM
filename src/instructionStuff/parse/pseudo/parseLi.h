//
// Created by lor on 8/26/25.
//

#ifndef PARSELI_H
#define PARSELI_H
#include <string>
#include <vector>

std::string parseLi(std::string str) {
    str.erase(0 ,str.find_first_not_of("   "));
    str.erase(0, str.find(' '));

    int bin = 0;

    std::stringstream strStream(str);
    std::string intermediate;
    std::vector<std::string> tokens;

    while (std::getline(strStream, intermediate, ',')) {
        tokens.push_back(utils::getFirstWord(intermediate));
    }

    std::string lowerInst = "";
    std::string upperInst = "lui";
};

#endif //PARSELI_H
