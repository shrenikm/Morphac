#include "mechanics/models/include/diffdrive_model.h"

namespace morphac {
namespace mechanics {
namespace models {

using std::cos;
using std::sin;
using std::string;

using Eigen::MatrixXd;
using Eigen::VectorXd;

using morphac::mechanics::models::KinematicModel;
using morphac::constructs::ControlInput;
using morphac::constructs::State;
using morphac::constructs::Pose;

DiffDriveModel::DiffDriveModel(const string name, const double radius,
                               const double length)
    : KinematicModel(name, 3, 0, 2), radius(radius), length(length) {}

void DiffDriveModel::ComputeStateDerivative(const State& state,
                                            const ControlInput& input,
                                            State& derivative) const {
  MORPH_REQUIRE(
      state.get_size_pose() == 3, std::invalid_argument,
      "Pose component of the state needs to be of size 3 [x, y, theta]");
  MORPH_REQUIRE(state.is_velocity_empty(), std::invalid_argument,
                "Velocity component of the state must be empty.");
  MORPH_REQUIRE(input.get_size() == 2, std::invalid_argument,
                "Control input must be of size 1.");
  MORPH_REQUIRE(
      derivative.get_size_pose() == 3, std::invalid_argument,
      "Pose component of the derivative needs to be of size 3 [x, y, theta]");
  MORPH_REQUIRE(derivative.is_velocity_empty(), std::invalid_argument,
                "Velocity component of the derivative must be empty.");
  VectorXd pose_derivative(3);
  double theta = state.get_pose()(2);

  MatrixXd F = VectorXd::Zero(3);
  MatrixXd G(2, 3);

  G << radius * 0.5 * cos(theta), radius * 0.5 * cos(theta),
      radius * 0.5 * sin(theta), radius * 0.5 * sin(theta), -radius / length,
      radius / length;

  pose_derivative = F + G * input.get_input_vector();
  derivative.set_pose_vector(pose_derivative);
}

State DiffDriveModel::ComputeStateDerivative(const State& state,
                                             const ControlInput& input) const {
  // Argument checks are performed by the other overloaded function.
  State derivative = State::CreateLike(state);
  ComputeStateDerivative(state, input, derivative);
  return derivative;
}

}  // namespace models
}  // namespace mechanics
}  // namespace morphac

