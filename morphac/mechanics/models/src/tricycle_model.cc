#include "mechanics/models/include/tricycle_model.h"

namespace morphac {
namespace mechanics {
namespace models {

using std::cos;
using std::sin;
using std::string;

using Eigen::MatrixXd;
using Eigen::VectorXd;

using morphac::mechanics::models::KinematicModel;
using morphac::constructs::Input;
using morphac::constructs::State;

TricycleModel::TricycleModel(const string name, const double radius,
                             const double length)
    : KinematicModel(name, 4, 0, 2), radius(radius), length(length) {
  MORPH_REQUIRE(radius > 0, std::invalid_argument,
                "Tricycle wheel radius must be positive.");
  MORPH_REQUIRE(
      length > 0, std::invalid_argument,
      "Tricycle distance between the back and front wheels must be positive.");
}

State TricycleModel::ComputeStateDerivative(const State& state,
                                            const Input& input) const {
  MORPH_REQUIRE(
      state.get_size_pose() == 4, std::invalid_argument,
      "Pose component of the state needs to be of size 3 [x, y, theta]");
  MORPH_REQUIRE(state.IsVelocityEmpty(), std::invalid_argument,
                "Velocity component of the state must be empty.");
  MORPH_REQUIRE(input.get_size() == 2, std::invalid_argument,
                "Input must be of size 1.");

  VectorXd pose_derivative(4);
  double theta = state.get_pose()(2);
  double alpha = state.get_pose()(3);

  // Equation of the form xdot = F(x) + G(x)u
  MatrixXd F = VectorXd::Zero(4);
  MatrixXd G(4, 2);

  G << radius * cos(alpha) * cos(theta), 0, radius * cos(alpha) * sin(theta), 0,
      (radius / length) * sin(alpha), 0, 0, 1;

  pose_derivative = F + G * input.get_input_vector();

  State derivative = State::CreateLike(state);
  derivative.set_pose_vector(pose_derivative);

  return derivative;
}

}  // namespace models
}  // namespace mechanics
}  // namespace morphac

