#include "mechanics/models/include/diffdrive_model.h"

namespace morphac {
namespace mechanics {
namespace models {

using std::cos;
using std::sin;

using Eigen::MatrixXd;
using Eigen::VectorXd;

using morphac::utils::NormalizeAngle;
using morphac::mechanics::models::KinematicModel;
using morphac::constructs::ControlInput;
using morphac::constructs::State;

DiffDriveModel::DiffDriveModel(const double radius, const double length)
    : KinematicModel(3, 0, 2), radius(radius), length(length) {
  MORPH_REQUIRE(radius > 0, std::invalid_argument,
                "Diffdrive wheel radius must be positive.");
  MORPH_REQUIRE(length > 0, std::invalid_argument,
                "Diffdrive distance between the wheels must be positive.");
}

State DiffDriveModel::ComputeStateDerivative(
    const State& state, const ControlInput& control_input) const {
  MORPH_REQUIRE(
      state.get_pose_size() == 3, std::invalid_argument,
      "Pose component of the state needs to be of size 3 [x, y, theta]");
  MORPH_REQUIRE(state.IsVelocityEmpty(), std::invalid_argument,
                "Velocity component of the state must be empty.");
  MORPH_REQUIRE(control_input.get_size() == 2, std::invalid_argument,
                "ControlInput must be of size 2.");

  VectorXd pose_derivative(3);
  double theta = state.get_pose()(2);

  // Equation of the form xdot = F(x) + G(x)u
  MatrixXd F = VectorXd::Zero(3);
  MatrixXd G(3, 2);

  G << radius * 0.5 * cos(theta), radius * 0.5 * cos(theta),
      radius * 0.5 * sin(theta), radius * 0.5 * sin(theta), -radius / length,
      radius / length;

  pose_derivative = F + G * control_input.get_data();

  State derivative = State::CreateLike(state);
  derivative.set_pose_data(pose_derivative);

  return derivative;
}

State DiffDriveModel::NormalizeState(const State& state) const {
  // For the diffdrive model, we normalize the pose angle.
  State normalized_state = state;
  normalized_state(2) = NormalizeAngle(normalized_state(2));

  return normalized_state;
}

}  // namespace models
}  // namespace mechanics
}  // namespace morphac

