//
// Created by lor on 8/13/25.
//

#include <string>
#include <vector>

class LabelSection {
    public:
        std::string name = "";
        std::vector<std::string> lines;
        std::string data = "";
        int dataSize = 0;
        int address;
        LabelSection() {};
        LabelSection(std::string namee) {
            name = namee;
        };
};
