#include "assembler/instruction.h"
#include "parser/instruction/b_type.h"
#include "parser/instruction/env_type.h"
#include "parser/instruction/i_type.h"
#include "parser/instruction/j_type.h"
#include "parser/instruction/l_type.h"
#include "parser/instruction/r_type.h"
#include "parser/instruction/s_type.h"
#include "parser/instruction/u_type.h"
#include "utils/common.h"

std::string assembleInst(const std::string& line, const std::vector<LabelSection>& labels) {
    inst::structThing instObj;

    const std::string firstWord = utils::getFirstWord(line);
    for (const auto& i : inst::lookup) {
        if (firstWord == i.name) {
            instObj = i;
            break;
        }
    }

    if (instObj.name.empty()) return "";

    if (instObj.fmt == "ralu") return parseRALUType(instObj, line);
    if (instObj.fmt == "ialu") return parseIALUType(instObj, line, labels);
    if (instObj.fmt == "l") return parseLType(instObj, line, labels);
    if (instObj.fmt == "s") return parseSType(instObj, line, labels);
    if (instObj.fmt == "b") return parseBType(instObj, line);
    if (instObj.fmt == "j") return parseJType(instObj, line);
    if (instObj.fmt == "u") return parseUType(instObj, line);
    if (instObj.fmt == "env") return parseEnvType(instObj);

    return ""; // Default return if no match
}
