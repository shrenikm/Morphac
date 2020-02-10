#ifndef KINEMATIC_MODEL_H
#define KINEMATIC_MODEL_H

#include "Eigen/Dense"

#include "constructs/include/control_input.h"
#include "constructs/include/pose.h"
#include "constructs/include/state.h"
#include "constructs/include/velocity.h"

namespace morphac {
namespace mechanics {

class KinematicModel {
 public:
  KinematicModel(int size_pose, int size_velocity, int size_input);

  virtual morphac::constructs::State ComputeStateDerivative(
      const morphac::constructs::State& state,
      const morphac::constructs::ControlInput& input) = 0;
  virtual void ComputeStateDerivative(
      const morphac::constructs::State& state,
      const morphac::constructs::ControlInput& input,
      morphac::constructs::State& derivative) = 0;

  const int get_size_pose();
  const int get_size_velocity();
  const int get_size_input();

 protected:
  const int size_pose_;
  const int size_velocity_;
  const int size_input_;
};

}  // namespace constructs
}  // namespace morphac

#endif
