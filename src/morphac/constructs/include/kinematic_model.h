#ifndef KINEMATIC_MODEL_H
#define KINEMATIC_MODEL_H

#include "Eigen/Dense"

#include "constructs/include/state.h"
#include "constructs/include/control_input.h"

namespace morphac {
namespace constructs {

class KinematicModel {
  public:
    KinematicModel(const State& state, const ControlInput& input);
    virtual State& ComputeDerivative() = 0;

};

} // namespace constructs
} // namespace morphac

#endif
