#ifndef PILOT_BINDING_H
#define PILOT_BINDING_H

#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"

#include "robot/driver/include/pilot.h"

namespace morphac {
namespace robot {
namespace driver {
namespace binding {

// Trampoline class as the Pilot class is abstract.
class PyPilot : public morphac::robot::driver::Pilot {
 public:
  using Pilot::Pilot;

  morphac::constructs::Input Execute(
      const morphac::simulation::playground::PlaygroundState& playground_state,
      const int uid) const override {
    PYBIND11_OVERLOAD_PURE_NAME(morphac::constructs::Input, Pilot, "execute",
                                Execute, playground_state, uid);
  }
};

void define_pilot_binding(pybind11::module& m);

}  // namespace binding
}  // namespace driver
}  // namespace robot
}  // namespace morphac

#endif
