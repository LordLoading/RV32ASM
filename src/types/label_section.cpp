#include "types/label_section.h"
#include "optimizer/optimizer.h"

LabelSection::LabelSection(const std::string& name) {
    this->name = name;
}

int LabelSection::calculateSize() {
    this->dataSize = 0; // Reset before recalculating
    for (const auto& currentLine : this->lines) {
        this->dataSize += iUtils::getLineSize(currentLine);
    }
    return this->dataSize;
}

bool LabelSection::isText() const {
    for (const std::string& currentLine : this->lines) {
        if (iUtils::isInstruction(currentLine)) {
            return true;
        }
    }
    return false;
}

void LabelSection::optimize(bool verbose) {
    // Only optimize text sections (code), not data sections
    if (!isText()) return;

    // Convert lines to IR
    auto ir = optimizer::linesToIR(this->lines);

    // Create optimizer and add passes
    optimizer::Optimizer opt(verbose);
    opt.addPass(new optimizer::RedundantInstructionPass());
    opt.addPass(new optimizer::PeepholePass());
    opt.addPass(new optimizer::DeadCodeEliminationPass());

    // Run optimization
    opt.optimize(ir);

    // Convert back to lines
    this->lines = optimizer::irToLines(ir);
}
