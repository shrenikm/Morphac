#include "mechanics/models/include/tricycle_model.h"

namespace morphac {
namespace mechanics {
namespace models {

using std::cos;
using std::min;
using std::sin;

using Eigen::MatrixXd;
using Eigen::VectorXd;

using morphac::common::aliases::Point;
using morphac::constants::TricycleModelConstants;
using morphac::constructs::ControlInput;
using morphac::constructs::State;
using morphac::mechanics::models::KinematicModel;
using morphac::robot::blueprint::Footprint;
using morphac::utils::NormalizeAngle;

TricycleModel::TricycleModel(const double width, const double length)
    : KinematicModel(4, 0, 2), width(width), length(length) {
  MORPH_REQUIRE(width > 0, std::invalid_argument,
                "Tricycle distance between the back wheels must be positive.");
  MORPH_REQUIRE(
      length > 0, std::invalid_argument,
      "Tricycle distance between the back and front wheels must be positive.");
}

State TricycleModel::ComputeStateDerivative(
    const State& state, const ControlInput& control_input) const {
  MORPH_REQUIRE(state.get_pose_size() == 4, std::invalid_argument,
                "Pose component of the state needs to be of size 4 [x, y, "
                "theta, alpha].");
  MORPH_REQUIRE(state.IsVelocityEmpty(), std::invalid_argument,
                "Velocity component of the state must be empty.");
  MORPH_REQUIRE(control_input.get_size() == 2, std::invalid_argument,
                "ControlInput must be of size 2.");

  // It is to be noted that the width parameter does not affect any of the
  // computation for the tricycle model.
  VectorXd pose_derivative(4);
  double theta = state[2];
  double alpha = state[3];

  // Equation of the form xdot = F(x) + G(x)u
  MatrixXd F = VectorXd::Zero(4);
  MatrixXd G(4, 2);

  G << cos(alpha) * cos(theta), 0, cos(alpha) * sin(theta), 0,
      (1. / length) * sin(alpha), 0, 0, 1;

  pose_derivative = F + G * control_input.get_data();

  // Return the derivative.
  return State(pose_derivative, VectorXd::Zero(0));
}

State TricycleModel::NormalizeState(const State& state) const {
  // For the tricycle model, we normalize the heading and steering angles.
  State normalized_state = state;
  normalized_state[2] = NormalizeAngle(normalized_state[2]);
  normalized_state[3] = NormalizeAngle(normalized_state[3]);

  return normalized_state;
}

Footprint TricycleModel::DefaultFootprint() const {
  // Default rounded rectangle footprint.
  // Buffer lengths that defines how much the footprint extends out of the frame
  // defined by width, length.
  double footprint_x_buffer =
      this->length * TricycleModelConstants::DEFAULT_LENGTH_BUFFER_SCALER +
      TricycleModelConstants::DEFAULT_LENGTH_BUFFER;
  double footprint_y_buffer =
      this->length * TricycleModelConstants::DEFAULT_WIDTH_BUFFER_SCALER +
      TricycleModelConstants::DEFAULT_WIDTH_BUFFER;

  return Footprint::CreateRoundedRectangularFootprint(
      this->length + footprint_x_buffer, this->width + footprint_y_buffer, 0.,
      min(this->width, this->length) / 4., 0.1, Point(-this->length / 2, 0));
}

}  // namespace models
}  // namespace mechanics
}  // namespace morphac
