#ifndef KINEMATIC_MODEL_H
#define KINEMATIC_MODEL_H

#include <unordered_map>

#include "Eigen/Dense"

#include "constructs/include/control_input.h"
#include "constructs/include/pose.h"
#include "constructs/include/state.h"
#include "constructs/include/velocity.h"

namespace morphac {
namespace mechanics {

// The parameters of this class need to be kept const as they serve as a kind
// of data class as well. Nothing is private to prevent unnecessary private
// member creation in the derived classes which would have additional data
// members
class KinematicModel {
 public:
  KinematicModel(const std::string name, const int size_pose,
                 const int size_velocity, const int size_input);

  virtual morphac::constructs::State ComputeStateDerivative(
      const morphac::constructs::State& state,
      const morphac::constructs::ControlInput& input) const = 0;
  virtual void ComputeStateDerivative(
      const morphac::constructs::State& state,
      const morphac::constructs::ControlInput& input,
      morphac::constructs::State& derivative) const = 0;

  const int get_size_pose() const;
  const int get_size_velocity() const;
  const int get_size_input() const;

  const std::string name;
  const int size_pose;
  const int size_velocity;
  const int size_input;
};

}  // namespace constructs
}  // namespace morphac

#endif
