#ifndef KINEMATIC_MODEL_H
#define KINEMATIC_MODEL_H

#include "Eigen/Dense"

#include "constructs/include/input.h"
#include "constructs/include/state.h"

namespace morphac {
namespace mechanics {
namespace models {

// The parameters of this class need to be kept const as they serve as a kind
// of data class as well. Nothing is private to prevent unnecessary private
// member creation in the derived classes which would have additional data
// members
class KinematicModel {
 public:
  KinematicModel(const int pose_size, const int velocity_size,
                 const int input_size);

  virtual morphac::constructs::State ComputeStateDerivative(
      const morphac::constructs::State& state,
      const morphac::constructs::Input& input) const = 0;

  // Function to normalize the given state acccording to the model. This may
  // involve angle normalization, positional normalization, etc.
  // This is useful in cases like simulation where we expect the state to always
  // be primed.
  virtual morphac::constructs::State NormalizeState(
      const morphac::constructs::State& state) const;

  const int pose_size;
  const int velocity_size;
  const int input_size;
};

}  // namespace models
}  // namespace mechanics
}  // namespace morphac

#endif
