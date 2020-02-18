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



}  // namespace models
}  // namespace mechanics
}  // namespace morphac

