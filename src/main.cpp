#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <regex>
#include <algorithm>

#include "types/label_section.h"
#include "assembler/line.h"

// the code from here...
void exportLogisimV3_0(const std::string &bytes, const std::string &outFilename) {
    std::ofstream outFile(outFilename);
    if (!outFile) {
        throw std::ios_base::failure(
            "Failed to open output file '" + outFilename + "'.");
    }

    outFile << "v3.0 hex words plain\n";
    for (const uint8_t &byte: bytes) {
        outFile << byte;
    }
    outFile << "\n";
}

void printUsage(const char *progName) {
    std::cout << "Usage: " << progName << " [options]\n\n"
            << "Options:\n"
            << "  -i, --input <file>    Input assembly file (default: assembleMe.s)\n"
            << "  -o, --output <file>   Output Logisim v3 hex file (default: program_v3.hex)\n"
            << "  -O, --optimize        Enable optimization passes\n"
            << "  -v, --verbose         Verbose output (show optimization details)\n"
            << "  -h, --help            Show this help message\n";
}

int main(int argc, char *argv[]) {
    std::string inputFile = "assembleMe.s";
    std::string outputFile = "program_v3.hex";
    bool optimize = false;
    bool verbose = false;

    for (int i = 1; i < argc; ++i) {
        if (std::string arg = argv[i]; arg == "-i" || arg == "--input") {
            if (i + 1 < argc) {
                inputFile = argv[++i];
            } else {
                std::cerr << arg << " requires a filename argument\n";
                return 1;
            }
        } else if (arg == "-o" || arg == "--output") {
            if (i + 1 < argc) {
                outputFile = argv[++i];
            } else {
                std::cerr << arg << " requires a filename argument\n";
                return 1;
            }
        } else if (arg == "-O" || arg == "--optimize") {
            optimize = true;
        } else if (arg == "-v" || arg == "--verbose") {
            verbose = true;
        } else if (arg == "-h" || arg == "--help") {
            printUsage(argv[0]);
            return 0;
        } else {
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
    // ... to here was stolen from zOnlyKroks's assembler cos i was too lazy ._.

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(input, line)) {
        lines.push_back(line);
    }

    auto currentLabel = LabelSection();
    std::vector<LabelSection> labels;

    // create label sections
    for (const std::string& currentLine: lines) {
        if (std::regex_match(currentLine, std::regex(".*:"))) {
            if (!currentLabel.name.empty()) {
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

    // figure out order of labels
    std::vector<LabelSection> sortedLabels;

    // always move the "main" label to the start of the program
    auto mainIt = std::find_if(labels.begin(), labels.end(),
        [](const LabelSection& label) { return label.name == "main"; });

    if (mainIt != labels.end()) {
        sortedLabels.push_back(*mainIt);
        sortedLabels.back().address = 0;
    }

    // move the text sections before the data sections (excluding main which is already added)
    for (const auto& label : labels) {
        if (label.name != "main" && label.isText()) {
            sortedLabels.push_back(label);
        }
    }

    // push the rest after (only data left so no need to keep sorting)
    for (const auto& label : labels) {
        if (label.name != "main" && !label.isText()) {
            sortedLabels.push_back(label);
        }
    }

    // Apply optimizations if requested
    if (optimize) {
        if (verbose) {
            std::cout << "Running optimization passes...\n";
        }
        for (auto& label : sortedLabels) {
            label.optimize(verbose);
        }
        if (verbose) {
            std::cout << "Optimization complete.\n\n";
        }
    }

    //figure out addresses
    for (size_t i = 0; i < sortedLabels.size(); i++) {
        sortedLabels[i].calculateSize();

        if (i > 0) {
            const LabelSection& prevLabel = sortedLabels[i - 1];
            sortedLabels[i].address = prevLabel.address + prevLabel.dataSize;
            std::cout << sortedLabels[i].name << ": " << sortedLabels[i].address << "\n";
        }
    }

    std::string data;

    for (const auto& label : sortedLabels) {
        for (size_t lineIdx = 0; lineIdx < label.lines.size(); ++lineIdx) {
            try {
                data += assembleLine(label.lines[lineIdx], sortedLabels);
            } catch (const std::exception& e) {
                std::cerr << "Error in label '" << label.name
                          << "' at line " << (lineIdx + 1)
                          << ": " << e.what() << "\n"
                          << "  Line content: " << label.lines[lineIdx] << "\n";
                return 1;
            }
        }
    }

    std::cout << data << std::endl;
    exportLogisimV3_0(data, outputFile);

    return 0;
}
