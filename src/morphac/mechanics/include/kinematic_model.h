#ifndef KINEMATIC_MODEL_H
#define KINEMATIC_MODEL_H

#include "Eigen/Dense"

#include "constructs/include/control_input.h"
#include "constructs/include/pose.h"
#include "constructs/include/state.h"
#include "constructs/include/velocity.h"

namespace morphac {
namespace constructs {

class KinematicModel {
 public:
  KinematicModel(const std::shared_ptr<State>& state,
                 const std::shared_ptr<ControlInput>& input);
  virtual const State& ComputeDerivative() = 0;

 protected:
  const int size_pose_;
  const int size_velocity_;
  const int size_input_;
  const std::shared_ptr<State>& state_;
  const std::shared_ptr<ControlInput>& input_;
  std::shared_ptr<State> derivative_;
};

}  // namespace constructs
}  // namespace morphac

#endif
