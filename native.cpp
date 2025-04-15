// Compile with `c++ -std=c++17 -Isignalgp-lite/include native.cpp`

#include <iostream>

#include "World.h"

// This is the main function for the NATIVE version of this project.

int main(int argc, char *argv[]) {
  emp::Random random(2);
  OrgWorld world(random);
  // Some SignalGP-Lite functionality uses its own emp::Random instance
  // so it's important to set that seed too when the main Random is created
  sgpl::tlrand.Get().ResetSeed(2);

  Organism* new_org = new Organism(&world, 0);
  world.Inject(*new_org);
  world.Resize(10,10);

  for (int update = 0; update < 400; update++) {
    world.Update();
  }

}
