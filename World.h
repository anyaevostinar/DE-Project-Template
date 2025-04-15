#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"

#include "Org.h"

class OrgWorld : public emp::World<Organism> {
  emp::vector<emp::WorldPosition> reproduce_queue;

public:
  OrgWorld(emp::Random &_random) : emp::World<Organism>(_random) {}

  ~OrgWorld() {}

  const pop_t &GetPopulation() { return pop; }

  void Update() {
    emp::World<Organism>::Update();

    //Process each organism
    emp::vector<size_t> schedule = emp::GetPermutation(GetRandom(), GetSize());
    for (int i : schedule) {
      if (!IsOccupied(i)) {
        continue;
      }
      pop[i]->Process(i);
    }

    //Time to allow reproduction for any organisms that ran the reproduce instruction
    for (emp::WorldPosition location : reproduce_queue) {
      if (!IsOccupied(location)) {
        return;
      }
      std::optional<Organism> offspring =
          pop[location.GetIndex()]->CheckReproduction();
      if (offspring.has_value()) {
        DoBirth(offspring.value(), location.GetIndex());
      }
    }
    reproduce_queue.clear();
  }

  void CheckOutput(float output, OrgState &state) {
    //TODO: Check if the organism solved a task!
  }

  void ReproduceOrg(emp::WorldPosition location) {
    // Wait until after all organisms have been processed to perform
    // reproduction. If reproduction happened immediately then the child could
    // ovewrite the parent, and then we would be running the code of a deleted
    // organism
    reproduce_queue.push_back(location);
  }
};

#endif