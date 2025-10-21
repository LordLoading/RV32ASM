//
// Assembly-time optimization pass system
//

#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "optimizer/instruction_ir.h"
#include <vector>
#include <string>

namespace optimizer {

    // Base class for optimization passes
    class OptimizationPass {
    public:
        virtual ~OptimizationPass() = default;
        virtual std::string getName() const = 0;
        virtual bool run(std::vector<InstructionIR>& instructions) = 0;
    };

    // Remove instructions that do nothing
    class RedundantInstructionPass : public OptimizationPass {
    public:
        std::string getName() const override { return "Redundant Instruction Removal"; }
        bool run(std::vector<InstructionIR>& instructions) override;
    };

    // Remove dead code after unconditional jumps
    class DeadCodeEliminationPass : public OptimizationPass {
    public:
        std::string getName() const override { return "Dead Code Elimination"; }
        bool run(std::vector<InstructionIR>& instructions) override;
    };

    // Peephole optimizations on instruction sequences
    class PeepholePass : public OptimizationPass {
    public:
        std::string getName() const override { return "Peephole Optimization"; }
        bool run(std::vector<InstructionIR>& instructions) override;

    private:
        // Check for specific patterns
        bool optimizeAddZero(std::vector<InstructionIR>& instructions, size_t idx);
        bool optimizeMoveToSelf(std::vector<InstructionIR>& instructions, size_t idx);
        bool optimizeDoubleNegation(std::vector<InstructionIR>& instructions, size_t idx);
        bool optimizeLoadStore(std::vector<InstructionIR>& instructions, size_t idx);
    };

    // Main optimizer class that runs all passes
    class Optimizer {
    public:
        Optimizer(bool verbose = true);
        ~Optimizer();

        void addPass(OptimizationPass* pass);
        void optimize(std::vector<InstructionIR>& instructions);

        int getTotalOptimizations() const { return totalOptimizations; }

    private:
        std::vector<OptimizationPass*> passes;
        bool verbose;
        int totalOptimizations;
    };

    // Helper: Convert lines to IR
    std::vector<InstructionIR> linesToIR(const std::vector<std::string>& lines);

    // Helper: Convert IR back to lines
    std::vector<std::string> irToLines(const std::vector<InstructionIR>& instructions);

} // namespace optimizer

#endif // OPTIMIZER_H
