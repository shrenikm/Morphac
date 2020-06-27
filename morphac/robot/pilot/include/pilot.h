#ifndef PILOT_H
#define PILOT_H

#include "constructs/include/input.h"
#include "simulation/include/playground_state.h"

namespace morphac {
namespace robot {
namespace pilot {

class Pilot {
 public:
  Pilot();

  virtual morphac::constructs::Input Execute(
      const morphac::simulation::PlaygroundState& playground_state,
      const int uid) const = 0;
};

}  // namespace pilot
}  // namespace robot
}  // namespace morphac

#endif
