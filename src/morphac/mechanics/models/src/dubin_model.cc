#include "mechanics/models/include/dubin_model.h"

namespace morphac {
namespace mechanics {
namespace models {

using std::string;

using Eigen::VectorXd;

using morphac::mechanics::models::KinematicModel;
using morphac::constructs::ControlInput;
using morphac::constructs::State;

DubinModel::DubinModel(const string name, const double speed)
    : KinematicModel(name, 3, 3, 1), speed(speed) {}

void DubinModel::ComputeStateDerivative(const State& state,
                                        const ControlInput& input,
                                        State& derivative) const {
  VectorXd pose_derivative(3), velocity_derivative(3);
}

State DubinModel::ComputeStateDerivative(const State& state,
                                         const ControlInput& input) const {}

}  // namespace models
}  // namespace mechanics
}  // namespace morphac
