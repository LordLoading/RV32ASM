#include "assembler/pseudo.h"
#include "utils/common.h"

// Include all parse headers
#include "parser/pseudo/call.h"
#include "parser/pseudo/j.h"
#include "parser/pseudo/jr.h"
#include "parser/pseudo/li.h"
#include "parser/pseudo/mv.h"
#include "parser/pseudo/neg.h"
#include "parser/pseudo/nop.h"
#include "parser/pseudo/not.h"
#include "parser/pseudo/pop_b.h"
#include "parser/pseudo/pop_h.h"
#include "parser/pseudo/pop_w.h"
#include "parser/pseudo/push_b.h"
#include "parser/pseudo/push_h.h"
#include "parser/pseudo/push_w.h"
#include "parser/pseudo/ret.h"

std::string assemblePseudo(const std::string& line, const std::vector<LabelSection>& labels) {
    const std::string fw = utils::getFirstWord(line);

    if (fw == "li") return parseLi(line, labels);
    if (fw == "mv") return parseMv(line, labels);
    if (fw == "not") return parseNot(line, labels);
    if (fw == "nop") return parseNop(line, labels);
    if (fw == "neg") return parseNeg(line, labels);
    if (fw == "call") return parseCall(line, labels);
    if (fw == "ret") return parseRet(line, labels);
    if (fw == "j") return parseJ(line, labels);
    if (fw == "jr") return parseJr(line, labels);
    if (fw == "pushb") return parsePushB(line, labels);
    if (fw == "popb") return parsePopB(line, labels);
    if (fw == "pushh") return parsePushH(line, labels);
    if (fw == "poph") return parsePopH(line, labels);
    if (fw == "pushw") return parsePushW(line, labels);
    if (fw == "popw") return parsePopW(line, labels);
    return "";
}
