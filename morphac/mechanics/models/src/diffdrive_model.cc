#include "mechanics/models/include/diffdrive_model.h"

namespace morphac {
namespace mechanics {
namespace models {

using std::cos;
using std::sin;

using Eigen::MatrixXd;
using Eigen::VectorXd;

using morphac::constants::DiffdriveModelConstants;
using morphac::constructs::ControlInput;
using morphac::constructs::State;
using morphac::mechanics::models::KinematicModel;
using morphac::robot::blueprint::Footprint;
using morphac::utils::NormalizeAngle;

DiffdriveModel::DiffdriveModel(const double radius, const double width)
    : KinematicModel(3, 0, 2), radius(radius), width(width) {
  MORPH_REQUIRE(radius > 0, std::invalid_argument,
                "Diffdrive wheel radius must be positive.");
  MORPH_REQUIRE(width > 0, std::invalid_argument,
                "Diffdrive distance between the wheels must be positive.");
}

State DiffdriveModel::ComputeStateDerivative(
    const State& state, const ControlInput& control_input) const {
  MORPH_REQUIRE(
      state.get_pose_size() == 3, std::invalid_argument,
      "Pose component of the state needs to be of size 3 [x, y, theta]");
  MORPH_REQUIRE(state.IsVelocityEmpty(), std::invalid_argument,
                "Velocity component of the state must be empty.");
  MORPH_REQUIRE(control_input.get_size() == 2, std::invalid_argument,
                "ControlInput must be of size 2.");

  VectorXd pose_derivative(3);
  double theta = state[2];

  // Equation of the form xdot = F(x) + G(x)u
  MatrixXd F = VectorXd::Zero(3);
  MatrixXd G(3, 2);

  G << radius * 0.5 * cos(theta), radius * 0.5 * cos(theta),
      radius * 0.5 * sin(theta), radius * 0.5 * sin(theta), -radius / width,
      radius / width;

  pose_derivative = F + G * control_input.get_data();

  // Return the derivative.
  return State(pose_derivative, VectorXd::Zero(0));
}

State DiffdriveModel::NormalizeState(const State& state) const {
  // For the diffdrive model, we normalize the pose angle.
  State normalized_state = state;
  normalized_state[2] = NormalizeAngle(normalized_state[2]);

  return normalized_state;
}

Footprint DiffdriveModel::DefaultFootprint() const {
  // Default circular footprint.
  // Buffer length that defines how much the footprint extends out of the frame
  // defined by width, length.
  double footprint_radius_buffer =
      this->width * DiffdriveModelConstants::DEFAULT_RADIUS_BUFFER_SCALER +
      DiffdriveModelConstants::DEFAULT_RADIUS_BUFFER;

  return Footprint::CreateCircularFootprint(
      this->width / 2. + footprint_radius_buffer, 0.1);
}

}  // namespace models
}  // namespace mechanics
}  // namespace morphac
