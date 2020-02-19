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
using morphac::constructs::ControlInput;
using morphac::constructs::State;
using morphac::constructs::Pose;

TricycleModel::TricycleModel(const string name, const double radius,
                             const double length)
    : KinematicModel(name, 4, 0, 2), radius(radius), length(length) {
  MORPH_REQUIRE(radius > 0, std::invalid_argument,
                "Tricycle wheel radius must be positive.");
  MORPH_REQUIRE(
      length > 0, std::invalid_argument,
      "Tricycle distance between the back and front wheels must be positive.");
}

}  // namespace models
}  // namespace mechanics
}  // namespace morphac

