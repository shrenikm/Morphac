#ifndef PILOT_BINDING_H
#define PILOT_BINDING_H

#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"

#include "robot/pilot/include/pilot.h"

namespace morphac {
namespace robot {
namespace pilot {
namespace binding {

// Trampoline class as the Pilot class is abstract.
class PyPilot : public morphac::robot::pilot::Pilot {
 public:
  using Pilot::Pilot;

  morphac::constructs::Input Execute(
      const morphac::simulation::PlaygroundState& playground_state,
      const int uid) override {
    PYBIND11_OVERLOAD_PURE_NAME(morphac::constructs::Input, Pilot, "execute",
                                Execute, playground, uid);
  }
};

void define_pilot_binding(pybind11::module& m);

}  // namespace binding
}  // namespace pilot
}  // namespace robot
}  // namespace morphac

#endif
