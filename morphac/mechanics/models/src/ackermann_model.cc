#include "mechanics/models/include/ackermann_model.h"

namespace morphac {
namespace mechanics {
namespace models {

using std::atan2;
using std::cos;
using std::fabs;
using std::min;
using std::sin;
using std::tan;
using std::vector;

using Eigen::MatrixXd;
using Eigen::VectorXd;

using morphac::common::aliases::Point;
using morphac::constants::AckermannModelConstants;
using morphac::constructs::ControlInput;
using morphac::constructs::State;
using morphac::math::geometry::RoundedRectangleShape;
using morphac::mechanics::models::KinematicModel;
using morphac::robot::blueprint::Footprint;
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

  // Phi cannot be greater than 90 degrees (in either direction) as it is not a
  // valid steering angle for the ackermann model. The kinematic model contains
  // a tan(phi) which makes this undefined.
  // Note that we assume that the state is already normalized.
  MORPH_REQUIRE(
      (phi > -M_PI / 2) && (phi < M_PI / 2), std::invalid_argument,
      "Invalid steering angle. It must lie between -pi / 2 and pi / 2.");

  // Equation of the form xdot = F(x) + G(x)u
  MatrixXd F = VectorXd::Zero(4);
  MatrixXd G(4, 2);

  G << cos(theta), 0, sin(theta), 0, tan(phi) / length, 0, 0, 1;

  pose_derivative = F + G * control_input.get_data();

  // Return the derivative.
  return State(pose_derivative, VectorXd::Zero(0));
}

State AckermannModel::NormalizeState(const State& state) const {
  // Normalizing the heading and steering angles.
  State normalized_state = state;
  normalized_state[2] = NormalizeAngle(normalized_state[2]);
  normalized_state[3] = NormalizeAngle(normalized_state[3]);

  return normalized_state;
}

double AckermannModel::ComputeInnerSteeringAngle(
    const double ideal_steering_angle) const {
  return NormalizeAngle(atan2(2 * length * sin(ideal_steering_angle),
                              2 * length * cos(ideal_steering_angle) -
                                  width * sin(ideal_steering_angle)));
}

double AckermannModel::ComputeOuterSteeringAngle(
    const double ideal_steering_angle) const {
  return NormalizeAngle(atan2(2 * length * sin(ideal_steering_angle),
                              2 * length * cos(ideal_steering_angle) +
                                  width * sin(ideal_steering_angle)));
}

vector<double> AckermannModel::ComputeSteeringAngles(
    const double ideal_steering_angle) const {
  // We compute the angles using the absoltue ideal angle first. By the nature
  // of symmetry, we just negate the values after if the the ideal angle was
  // negative. Passing a negative value into the computation doesn't correctly
  // for some reason.
  double inner_steering_angle =
      ComputeInnerSteeringAngle(fabs(ideal_steering_angle));
  double outer_steering_angle =
      ComputeOuterSteeringAngle(fabs(ideal_steering_angle));
  if (ideal_steering_angle < 0.) {
    inner_steering_angle = -inner_steering_angle;
    outer_steering_angle = -outer_steering_angle;
  }
  vector<double> steering_angles = {inner_steering_angle, outer_steering_angle};
  return steering_angles;
}

Footprint AckermannModel::DefaultFootprint() const {
  // Default rounded rectangle footprint.
  // Buffer lengths that defines how much the footprint extends out of the frame
  // defined by width, length.
  double footprint_x_buffer =
      this->length * AckermannModelConstants::DEFAULT_LENGTH_BUFFER_SCALER +
      AckermannModelConstants::DEFAULT_LENGTH_BUFFER;
  double footprint_y_buffer =
      this->length * AckermannModelConstants::DEFAULT_WIDTH_BUFFER_SCALER +
      AckermannModelConstants::DEFAULT_WIDTH_BUFFER;

  return Footprint::CreateRoundedRectangularFootprint(
      RoundedRectangleShape{
          this->length + footprint_x_buffer, this->width + footprint_y_buffer,
          0., min(this->width, this->length) / 4., Point(-this->length / 2, 0)},
      0.1);
}

}  // namespace models
}  // namespace mechanics
}  // namespace morphac
