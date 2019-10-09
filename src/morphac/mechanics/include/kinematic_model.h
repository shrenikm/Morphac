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
  KinematicModel(
      const std::shared_ptr<morphac::constructs::State>& state,
      const std::shared_ptr<morphac::constructs::ControlInput>& input);
  virtual void ComputeDerivative() = 0;
  const morphac::constructs::State& get_derivative() const;
  const morphac::constructs::State& get_state() const;
  const morphac::constructs::ControlInput& get_input() const;

 protected:
  const int size_pose_;
  const int size_velocity_;
  const int size_input_;
  const std::shared_ptr<morphac::constructs::State>& state_;
  const std::shared_ptr<morphac::constructs::ControlInput>& input_;
  std::shared_ptr<morphac::constructs::State> derivative_;
};

}  // namespace constructs
}  // namespace morphac

#endif
