#ifndef ORGSTATE_H
#define ORGSTATE_H

#include "emp/Evolve/World_structure.hpp"
#include <cstddef>

// This forward declaration is necessary since the world contains organisms,
// which contain cpus, which contain the state, so if the state could actually
// access the definition of the world there would be a cycle.
class OrgWorld;

struct OrgState {
  emp::Ptr<OrgWorld> world;

  //Array for tracking the four most recent input values
  uint32_t last_inputs[4];
  //Index of the most recent input value in array
  size_t last_input_idx;
  //How many points this organism has currently
  double points;
  //Needs to know current location for possible reproduction
  emp::WorldPosition current_location;

  /**
  * Adds an input number to the tracker
  */
  void add_input(uint32_t input) {
    last_inputs[last_input_idx] = input;
    last_input_idx = (last_input_idx + 1) % 4;
  }
};

#endif