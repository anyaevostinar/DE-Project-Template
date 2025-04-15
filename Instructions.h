#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "OrgState.h"
#include "sgpl/library/OpLibraryCoupler.hpp"
#include "sgpl/library/prefab/ArithmeticOpLibrary.hpp"
#include "sgpl/library/prefab/NopOpLibrary.hpp"
#include "sgpl/operations/flow_global/Anchor.hpp"
#include "sgpl/program/Instruction.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"
//#include <_types/_uint32_t.h>

/**
 * A custom instruction that outputs the value of a register as the (possible)
 * solution to a task, and then gets a new input value and stores it in the same
 * register.
 */
struct IOInstruction {
  template <typename Spec>
  static void run(sgpl::Core<Spec> &core, const sgpl::Instruction<Spec> &inst,
                  const sgpl::Program<Spec> &,
                  typename Spec::peripheral_t &state) noexcept {
    uint32_t output = core.registers[inst.args[0]];
    state.world->CheckOutput(output, state);

    uint32_t input = sgpl::tlrand.Get().GetUInt();
    core.registers[inst.args[0]] = input;
    state.add_input(input);
  }

  static std::string name() { return "IO"; }
  static size_t prevalence() { return 1; }
};

struct NandInstruction {
  template <typename Spec>
  static void run(sgpl::Core<Spec> &core, const sgpl::Instruction<Spec> &inst,
                  const sgpl::Program<Spec> &,
                  typename Spec::peripheral_t &state) noexcept {
                    uint32_t reg_b = core.registers[inst.args[1]];
                    uint32_t reg_c = core.registers[inst.args[2]];
                    uint32_t nand_val = ~(reg_b & reg_c);

                    core.registers[inst.args[0]] = nand_val;
                  }
  static std::string name() { return "Nand"; }
  static size_t prevalence() { return 1; }
};

/**
 * A custom instruction that attempts to reproduce and produce a child organism,
 * if this organism has enough points.
 */
struct ReproduceInstruction {
  template <typename Spec>
  static void run(sgpl::Core<Spec> &core, const sgpl::Instruction<Spec> &inst,
                  const sgpl::Program<Spec> &,
                  typename Spec::peripheral_t &state) noexcept {
    if (state.points > 20) {
      state.world->ReproduceOrg(state.current_location);
      state.points = 0;
    }
    
  }

  static std::string name() { return "Reproduce"; }
  static size_t prevalence() { return 1; }
};



using Library =
    sgpl::OpLibraryCoupler<sgpl::NopOpLibrary, sgpl::BitwiseShift, sgpl::Increment, sgpl::Decrement,
    sgpl::Add, sgpl::Subtract, sgpl::global::JumpIfNot, sgpl::local::JumpIfNot, sgpl::global::Anchor, IOInstruction, NandInstruction,
                           ReproduceInstruction>;

using Spec = sgpl::Spec<Library, OrgState>;

#endif