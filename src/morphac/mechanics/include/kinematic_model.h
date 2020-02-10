#ifndef KINEMATIC_MODEL_H
#define KINEMATIC_MODEL_H

#include <string>
#include <unordered_map>

#include "Eigen/Dense"

#include "constructs/include/control_input.h"
#include "constructs/include/pose.h"
#include "constructs/include/state.h"
#include "constructs/include/velocity.h"

namespace morphac {
namespace mechanics {

class KinematicModel {
 public:
  KinematicModel(const int size_pose, const int size_velocity,
                 const int size_input);

  virtual morphac::constructs::State ComputeStateDerivative(
      const std::unordered_map<std::string, double>,
      const morphac::constructs::State& state,
      const morphac::constructs::ControlInput& input) const = 0;
  virtual void ComputeStateDerivative(
      const std::unordered_map<std::string, double>,
      const morphac::constructs::State& state,
      const morphac::constructs::ControlInput& input,
      morphac::constructs::State& derivative) const = 0;

  const int get_size_pose() const;
  const int get_size_velocity() const;
  const int get_size_input() const;

 protected:
  const int size_pose_;
  const int size_velocity_;
  const int size_input_;
};

}  // namespace constructs
}  // namespace morphac

#endif
