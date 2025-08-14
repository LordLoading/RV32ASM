#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <regex>

#include "src/LabelSection.cpp"
#include "src/utils.h"


void printUsage(const char* progName) {
    std::cout << "Usage: " << progName << " [options]\n\n"
              << "Options:\n"
              << "  -i, --input <file>    Input assembly file (default: assembleMe.s)\n"
              << "  -o, --output <file>   Output Logisim v3 hex file (default: program_v3.hex)\n"
              << "  -h, --help            Show this help message\n";
}

int main(int argc, char* argv[]) {
    std::string inputFile  = "assembleMe.s";
    std::string outputFile = "program_v3.hex";

    for (int i = 1; i < argc; ++i) {
        if (std::string arg = argv[i]; arg == "-i" || arg == "--input") {
            if (i + 1 < argc) {
                inputFile = argv[++i];
            } else {
                std::cerr << arg << " requires a filename argument\n";
                return 1;
            }
        }
        else if (arg == "-o" || arg == "--output") {
            if (i + 1 < argc) {
                outputFile = argv[++i];
            } else {
                std::cerr << arg << " requires a filename argument\n";
                return 1;
            }
        }
        else if (arg == "-h" || arg == "--help") {
            printUsage(argv[0]);
            return 0;
        }
        else {
            std::cerr << "Unknown option: " << arg << "\n";
            printUsage(argv[0]);
            return 1;
        }
    }

    std::ifstream input(inputFile);
    if (!input) {
        std::cerr << "Error: cannot open input file '" << inputFile << "'\n";
        return 1;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(input, line)) {
        lines.push_back(line);
    }

    LabelSection currentLabel;
    std::vector<LabelSection> labels;

    // create label sections
    for (int i = 0; i < lines.size(); ++i) {
        std::string line = lines[i];
        if (std::regex_match(line, std::regex(".*:"))) {
            if (currentLabel.name.size() > 0) labels.push_back(currentLabel);

            std::string labelName = line.substr(0, line.find(":"));
            currentLabel = LabelSection(labelName);
            continue;
        } else if (std::regex_match(line, std::regex("#.*"))) continue;
        else if (std::regex_match(line, std::regex("[\t ]*\n"))) continue;
        else currentLabel.lines.push_back(line);
    }

    // figure out section sizes
    for (int i = 0; i < labels.size(); ++i) {
        LabelSection label = labels[i];
        for (int j = 0; j < label.lines.size(); ++j) {
            std::string currentLine = label.lines[j];
            std::cout << getLineSize(currentLine) << std::endl;
        }
    }

    //test

    return 0;
}