//
// Instruction Intermediate Representation for optimization passes
//

#ifndef INSTRUCTION_IR_H
#define INSTRUCTION_IR_H

#include <string>
#include <vector>
#include <optional>

namespace optimizer {

    enum class IRType {
        INSTRUCTION,  // Real or pseudo instruction
        DIRECTIVE,    // .word, .byte, .string, etc.
        LABEL,        // Label definition
        DEAD          // Marked for removal
    };

    // Represents a parsed instruction before encoding
    struct InstructionIR {
        IRType type;
        std::string original;      // Original source line
        std::string mnemonic;      // Instruction name (e.g., "add", "li")
        std::vector<std::string> operands;  // Register names, immediates, labels
        bool reachable;            // For dead code elimination
        int originalLineNum;       // For error reporting

        InstructionIR()
            : type(IRType::INSTRUCTION), reachable(true), originalLineNum(0) {}

        InstructionIR(IRType t, const std::string& orig, int lineNum = 0)
            : type(t), original(orig), reachable(true), originalLineNum(lineNum) {}

        // Check if this is a no-op instruction
        bool isNop() const;

        // Check if this is an unconditional jump
        bool isUnconditionalJump() const;

        // Check if this writes to a register
        bool writesRegister(const std::string& reg) const;

        // Check if this reads from a register
        bool readsRegister(const std::string& reg) const;

        // Get the destination register (if any)
        std::optional<std::string> getDestRegister() const;
    };

    // Parse a line into IR format
    InstructionIR parseLineToIR(const std::string& line, int lineNum);

    // Convert IR back to assembly string
    std::string irToAssembly(const InstructionIR& ir);

} // namespace optimizer

#endif // INSTRUCTION_IR_H
