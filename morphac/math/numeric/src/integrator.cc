#include "math/numeric/include/integrator.h"

namespace morphac {
namespace math {
namespace numeric {

using morphac::mechanics::models::KinematicModel;

Integrator::Integrator(KinematicModel& kinematic_model)
    : kinematic_model_(kinematic_model) {}

}  // namespace numeric
}  // namespace math
}  // namespace morphac
