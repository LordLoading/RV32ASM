#include "optimizer/instruction_ir.h"
#include "utils/common.h"
#include "lookup/instruction.h"
#include "lookup/pseudo.h"
#include <sstream>
#include <algorithm>

namespace optimizer {

    bool InstructionIR::isNop() const {
        if (type != IRType::INSTRUCTION) return false;

        // Check for explicit nop
        if (mnemonic == "nop") return true;

        // Check for addi x0, x0, 0 (canonical nop)
        if (mnemonic == "addi" && operands.size() >= 3) {
            return operands[0] == "x0" && operands[1] == "x0" && operands[2] == "0";
        }

        // Check for mv x, x (move to self)
        if (mnemonic == "mv" && operands.size() >= 2) {
            return operands[0] == operands[1];
        }

        // Check for any instruction with x0 as destination
        if (operands.size() > 0 && operands[0] == "x0") {
            // Instructions that write to x0 are effectively nops
            // (except branches, stores, and system instructions)
            return mnemonic != "beq" && mnemonic != "bne" &&
                   mnemonic != "blt" && mnemonic != "bge" &&
                   mnemonic != "bltu" && mnemonic != "bgeu" &&
                   mnemonic != "sb" && mnemonic != "sh" && mnemonic != "sw" &&
                   mnemonic != "ecall" && mnemonic != "ebreak";
        }

        return false;
    }

    bool InstructionIR::isUnconditionalJump() const {
        if (type != IRType::INSTRUCTION) return false;
        return mnemonic == "j" || mnemonic == "jal" ||
               (mnemonic == "jalr" && operands.size() > 0 && operands[0] == "x0");
    }

    bool InstructionIR::writesRegister(const std::string& reg) const {
        if (type != IRType::INSTRUCTION || operands.empty()) return false;

        // Most instructions write to their first operand (destination register)
        // Exceptions: branches, stores, jumps that write to x0
        if (mnemonic == "beq" || mnemonic == "bne" || mnemonic == "blt" ||
            mnemonic == "bge" || mnemonic == "bltu" || mnemonic == "bgeu" ||
            mnemonic == "sb" || mnemonic == "sh" || mnemonic == "sw") {
            return false;
        }

        return operands[0] == reg;
    }

    bool InstructionIR::readsRegister(const std::string& reg) const {
        if (type != IRType::INSTRUCTION) return false;

        // Check all operands except the first (which is typically the destination)
        // For stores and branches, check all operands
        size_t startIdx = 0;
        if (mnemonic != "sb" && mnemonic != "sh" && mnemonic != "sw" &&
            mnemonic != "beq" && mnemonic != "bne" && mnemonic != "blt" &&
            mnemonic != "bge" && mnemonic != "bltu" && mnemonic != "bgeu") {
            startIdx = 1;
        }

        for (size_t i = startIdx; i < operands.size(); ++i) {
            // Handle offset(reg) format for loads/stores
            if (operands[i].find('(') != std::string::npos) {
                size_t openParen = operands[i].find('(');
                size_t closeParen = operands[i].find(')');
                if (openParen != std::string::npos && closeParen != std::string::npos) {
                    std::string regName = operands[i].substr(openParen + 1, closeParen - openParen - 1);
                    if (regName == reg) return true;
                }
            } else if (operands[i] == reg) {
                return true;
            }
        }

        return false;
    }

    std::optional<std::string> InstructionIR::getDestRegister() const {
        if (type != IRType::INSTRUCTION || operands.empty()) return std::nullopt;

        // Instructions that don't write to registers
        if (mnemonic == "beq" || mnemonic == "bne" || mnemonic == "blt" ||
            mnemonic == "bge" || mnemonic == "bltu" || mnemonic == "bgeu" ||
            mnemonic == "sb" || mnemonic == "sh" || mnemonic == "sw" ||
            mnemonic == "j") {
            return std::nullopt;
        }

        return operands[0];
    }

    InstructionIR parseLineToIR(const std::string& line, int lineNum) {
        InstructionIR ir(IRType::INSTRUCTION, line, lineNum);

        std::string trimmed = line;
        trimmed.erase(0, trimmed.find_first_not_of(" \t"));

        // Check for directives
        if (!trimmed.empty() && trimmed[0] == '.') {
            ir.type = IRType::DIRECTIVE;
            ir.mnemonic = utils::getFirstWord(trimmed);
            return ir;
        }

        // Get mnemonic
        ir.mnemonic = utils::getFirstWord(trimmed);

        // Parse operands
        size_t mnemonicEnd = trimmed.find_first_of(" \t");
        if (mnemonicEnd != std::string::npos) {
            std::string operandStr = trimmed.substr(mnemonicEnd);
            operandStr.erase(0, operandStr.find_first_not_of(" \t"));

            // Split by commas
            std::stringstream ss(operandStr);
            std::string token;
            while (std::getline(ss, token, ',')) {
                token.erase(0, token.find_first_not_of(" \t"));
                token.erase(token.find_last_not_of(" \t") + 1);
                if (!token.empty()) {
                    ir.operands.push_back(token);
                }
            }
        }

        return ir;
    }

    std::string irToAssembly(const InstructionIR& ir) {
        if (ir.type == IRType::DEAD) {
            return "";
        }

        if (ir.type == IRType::DIRECTIVE || ir.type == IRType::LABEL) {
            return ir.original;
        }

        // Reconstruct instruction
        std::string result = "    " + ir.mnemonic;
        for (size_t i = 0; i < ir.operands.size(); ++i) {
            if (i == 0) {
                result += " ";
            } else {
                result += ", ";
            }
            result += ir.operands[i];
        }
        return result;
    }

} // namespace optimizer
