#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <regex>

#include "src/Utils.h"
#include "src/LabelSection.h"


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

    LabelSection currentLabel = LabelSection();
    std::vector<LabelSection> labels;

    // create label sections
    for (std::string currentLine : lines) {
        if (std::regex_match(currentLine, std::regex(".*:"))) {
            if (currentLabel.name != "") {
                labels.push_back(currentLabel);
            }

            std::string labelName = currentLine.substr(0, currentLine.find(":"));
            currentLabel = LabelSection(labelName);

            continue;
        }
        if (std::regex_match(currentLine, std::regex("[\t ]*#.*"))) continue;
        if (std::regex_match(currentLine, std::regex("[\t ]*"))) continue;
        currentLabel.lines.push_back(currentLine);
    }

    labels.push_back(currentLabel);

    // figure out section sizes
    for (LabelSection label : labels) {
        label.calculateSize();
    }

    // figure out order of labels
    std::vector<LabelSection> sortedLabels = labels;
    //always move the "main" label to the start of the program
    for (int i = 0; i < labels.size(); ++i) {
        LabelSection label = labels[i];

        if (label.name == "main") {
            labels.erase(labels.begin() + i);
            sortedLabels.push_back(label);
            label.address = 0;
            break;
        }
    }
    //move the text sections before the data sections
    for (int i = 0; i < labels.size(); ++i) {
        LabelSection label = labels[i];

        if (label.isText() == true) {
            labels.erase(labels.begin() + i);
            sortedLabels.push_back(label);
        }
    }

    return 0;
}