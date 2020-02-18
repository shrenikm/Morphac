#ifndef DIFFDRIVE_MODEL_H
#define DIFFDRIVE_MODEL_H

#include "Eigen/Dense"

#include "common/error_handling/include/error_macros.h"
#include "constructs/include/control_input.h"
#include "constructs/include/state.h"
#include "mechanics/models/include/kinematic_model.h"

namespace morphac {
namespace mechanics {
namespace models {

class DiffDriveModel : public morphac::mechanics::models::KinematicModel {
 public:
  DiffDriveModel(const std::string name, const double radius,
                 const double length);
  void ComputeStateDerivative(const morphac::constructs::State& state,
                              const morphac::constructs::ControlInput& input,
                              morphac::constructs::State& derivative) const;
  morphac::constructs::State ComputeStateDerivative(
      const morphac::constructs::State& state,
      const morphac::constructs::ControlInput& input) const;

  const double radius;
  const double length;
};

}  // namespace models
}  // namespace mechancis
}  // namespace morphac

#endif
