#ifndef PARSEPUSHB_H
#define PARSEPUSHB_H
#include <string>
#include <vector>

class LabelSection;

std::string parsePushB(const std::string& line, const std::vector<LabelSection>& labels);

#endif //PARSEPUSHB_H
