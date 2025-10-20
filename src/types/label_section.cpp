#include "types/label_section.h"

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
