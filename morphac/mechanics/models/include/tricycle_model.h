#ifndef TRICYCLE_MODEL_H
#define TRICYCLE_MODEL_H

#include "Eigen/Dense"

#include "common/error_handling/include/error_macros.h"

#include "constructs/include/state.h"
#include "constructs/include/input.h"

#include "mechanics/models/include/kinematic_model.h"

namespace morphac {
namespace mechanics {
namespace models {

class TricycleModel : public morphac::mechanics::models::KinematicModel {
 public:
  TricycleModel(const std::string name, const double radius,
                const double length);

  morphac::constructs::State ComputeStateDerivative(
      const morphac::constructs::State& state,
      const morphac::constructs::Input& input) const;

  const double radius;
  const double length;
};

}  // namespace models
}  // namespace mechancis
}  // namespace morphac

#endif
