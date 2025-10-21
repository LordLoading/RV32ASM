#include "optimizer/optimizer.h"
#include <iostream>
#include <algorithm>

namespace optimizer {

    // RedundantInstructionPass implementation
    bool RedundantInstructionPass::run(std::vector<InstructionIR>& instructions) {
        bool changed = false;

        for (auto& instr : instructions) {
            if (instr.type == IRType::INSTRUCTION && instr.isNop()) {
                instr.type = IRType::DEAD;
                changed = true;
            }
        }

        return changed;
    }

    // DeadCodeEliminationPass implementation
    bool DeadCodeEliminationPass::run(std::vector<InstructionIR>& instructions) {
        bool changed = false;

        for (size_t i = 0; i < instructions.size(); ++i) {
            const auto& instr = instructions[i];

            // If we find an unconditional jump, mark following instructions as dead
            // until we hit a label or directive
            if (instr.type == IRType::INSTRUCTION && instr.isUnconditionalJump()) {
                for (size_t j = i + 1; j < instructions.size(); ++j) {
                    // Stop at labels or directives (potential jump targets)
                    if (instructions[j].type == IRType::LABEL ||
                        instructions[j].type == IRType::DIRECTIVE) {
                        break;
                    }

                    // Mark unreachable instructions as dead
                    if (instructions[j].type == IRType::INSTRUCTION &&
                        instructions[j].type != IRType::DEAD) {
                        instructions[j].type = IRType::DEAD;
                        changed = true;
                    }
                }
            }
        }

        return changed;
    }

    // PeepholePass implementation
    bool PeepholePass::run(std::vector<InstructionIR>& instructions) {
        bool changed = false;

        for (size_t i = 0; i < instructions.size(); ++i) {
            if (instructions[i].type != IRType::INSTRUCTION) continue;

            // Try various peephole optimizations
            changed |= optimizeAddZero(instructions, i);
            changed |= optimizeMoveToSelf(instructions, i);
            changed |= optimizeDoubleNegation(instructions, i);
            changed |= optimizeLoadStore(instructions, i);
        }

        return changed;
    }

    bool PeepholePass::optimizeAddZero(std::vector<InstructionIR>& instructions, size_t idx) {
        auto& instr = instructions[idx];

        // addi rd, rs, 0 -> mv rd, rs (or remove if rd == rs)
        if (instr.mnemonic == "addi" && instr.operands.size() >= 3) {
            if (instr.operands[2] == "0") {
                if (instr.operands[0] == instr.operands[1]) {
                    // addi x1, x1, 0 -> nop (mark as dead)
                    instr.type = IRType::DEAD;
                    return true;
                } else {
                    // addi x1, x2, 0 -> mv x1, x2
                    instr.mnemonic = "mv";
                    instr.operands.pop_back();
                    return true;
                }
            }
        }

        // add rd, rs, x0 -> mv rd, rs
        if (instr.mnemonic == "add" && instr.operands.size() >= 3) {
            if (instr.operands[2] == "x0" || instr.operands[2] == "zero") {
                instr.mnemonic = "mv";
                instr.operands.pop_back();
                return true;
            }
        }

        return false;
    }

    bool PeepholePass::optimizeMoveToSelf(std::vector<InstructionIR>& instructions, size_t idx) {
        auto& instr = instructions[idx];

        // mv x1, x1 -> nop (mark as dead)
        if (instr.mnemonic == "mv" && instr.operands.size() >= 2) {
            if (instr.operands[0] == instr.operands[1]) {
                instr.type = IRType::DEAD;
                return true;
            }
        }

        return false;
    }

    bool PeepholePass::optimizeDoubleNegation(std::vector<InstructionIR>& instructions, size_t idx) {
        // Look for: neg rd, rs; neg rd, rd -> (nothing - double negation cancels)
        if (idx + 1 >= instructions.size()) return false;

        auto& instr1 = instructions[idx];
        auto& instr2 = instructions[idx + 1];

        if (instr1.type != IRType::INSTRUCTION || instr2.type != IRType::INSTRUCTION) {
            return false;
        }

        if (instr1.mnemonic == "neg" && instr2.mnemonic == "neg" &&
            instr1.operands.size() >= 2 && instr2.operands.size() >= 2) {
            // neg t0, t1; neg t0, t0 -> mv t0, t1
            if (instr1.operands[0] == instr2.operands[0] &&
                instr1.operands[0] == instr2.operands[1]) {
                instr1.mnemonic = "mv";
                instr1.operands = {instr1.operands[0], instr1.operands[1]};
                instr2.type = IRType::DEAD;
                return true;
            }
        }

        return false;
    }

    bool PeepholePass::optimizeLoadStore(std::vector<InstructionIR>& instructions, size_t idx) {
        // Look for redundant load-store sequences
        if (idx + 1 >= instructions.size()) return false;

        auto& instr1 = instructions[idx];
        auto& instr2 = instructions[idx + 1];

        if (instr1.type != IRType::INSTRUCTION || instr2.type != IRType::INSTRUCTION) {
            return false;
        }

        // lw t0, 0(sp); sw t0, 0(sp) -> (can remove both if t0 not used elsewhere)
        // This is a simplified version - full implementation would need liveness analysis
        // For now, we skip this optimization

        return false;
    }

    // Optimizer implementation
    Optimizer::Optimizer(bool verbose)
        : verbose(verbose), totalOptimizations(0) {
    }

    Optimizer::~Optimizer() {
        for (auto* pass : passes) {
            delete pass;
        }
    }

    void Optimizer::addPass(OptimizationPass* pass) {
        passes.push_back(pass);
    }

    void Optimizer::optimize(std::vector<InstructionIR>& instructions) {
        totalOptimizations = 0;

        for (auto* pass : passes) {
            bool changed = pass->run(instructions);
            if (changed && verbose) {
                std::cout << "[Optimizer] " << pass->getName() << " made changes\n";
                totalOptimizations++;
            }
        }

        // Remove dead instructions
        instructions.erase(
            std::remove_if(instructions.begin(), instructions.end(),
                [](const InstructionIR& ir) { return ir.type == IRType::DEAD; }),
            instructions.end()
        );
    }

    // Helper functions
    std::vector<InstructionIR> linesToIR(const std::vector<std::string>& lines) {
        std::vector<InstructionIR> result;
        result.reserve(lines.size());

        for (size_t i = 0; i < lines.size(); ++i) {
            result.push_back(parseLineToIR(lines[i], static_cast<int>(i)));
        }

        return result;
    }

    std::vector<std::string> irToLines(const std::vector<InstructionIR>& instructions) {
        std::vector<std::string> result;
        result.reserve(instructions.size());

        for (const auto& ir : instructions) {
            if (ir.type != IRType::DEAD) {
                result.push_back(irToAssembly(ir));
            }
        }

        return result;
    }

} // namespace optimizer
