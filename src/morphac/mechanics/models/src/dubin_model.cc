#include "mechanics/models/include/dubin_model.h"

namespace morphac {
namespace mechanics {
namespace models {

using std::string;

using morphac::mechanics::models::KinematicModel;

DubinModel::DubinModel(const string name, const double speed)
    : KinematicModel(name, 3, 3, 1), speed(speed) {}

}  // namespace models
}  // namespace mechanics
}  // namespace morphac
