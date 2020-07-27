#ifndef PILOT_H
#define PILOT_H

#include "constructs/include/control_input.h"
#include "simulation/playground/include/playground_state.h"

namespace morphac {
namespace robot {
namespace pilot {

class Pilot {
 public:
  Pilot();

  virtual morphac::constructs::ControlInput Execute(
      const morphac::simulation::playground::PlaygroundState& playground_state,
      const int uid) const = 0;
};

}  // namespace pilot
}  // namespace robot
}  // namespace morphac

#endif
