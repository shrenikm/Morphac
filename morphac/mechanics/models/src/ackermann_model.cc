#include "mechanics/models/include/ackermann_model.h"

namespace morphac {
namespace mechanics {
namespace models {

using std::cos;
using std::sin;
using std::tan;

using Eigen::MatrixXd;
using Eigen::VectorXd;

using morphac::constructs::ControlInput;
using morphac::constructs::State;
using morphac::mechanics::models::KinematicModel;
using morphac::utils::NormalizeAngle;

AckermannModel::AckermannModel(const double width, const double length)
    : KinematicModel(4, 0, 2), width(width), length(length) {
  MORPH_REQUIRE(width > 0, std::invalid_argument,
                "Ackermann width between the wheels must be positive.");
  MORPH_REQUIRE(
      length > 0, std::invalid_argument,
      "Ackermann length between the front and back axles must be positive.");
}

State AckermannModel::ComputeStateDerivative(
    const State& state, const ControlInput& control_input) const {
  MORPH_REQUIRE(
      state.get_pose_size() == 4, std::invalid_argument,
      "Pose component of the state needs to be of size 4 [x, y, theta, phi].");
  MORPH_REQUIRE(state.IsVelocityEmpty(), std::invalid_argument,
                "Velocity component of the state must be empty.");
  MORPH_REQUIRE(control_input.get_size() == 2, std::invalid_argument,
                "ControlInput must be of size 2.");

  VectorXd pose_derivative(4);
  double theta = state[2];
  double phi = state[3];

  // Equation of the form xdot = F(x) + G(x)u
  MatrixXd F = VectorXd::Zero(4);
  MatrixXd G(4, 2);
}

}  // namespace models
}  // namespace mechanics
}  // namespace morphac
