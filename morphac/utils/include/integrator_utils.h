#ifndef INTEGRATOR_UTILS_H
#define INTEGRATOR_UTILS_H

#include <memory>

#include "math/numeric/include/all_integrators.h"
#include "mechanics/models/include/kinematic_model.h"

namespace morphac {
namespace utils {

std::unique_ptr<morphac::math::numeric::Integrator> IntegratorFromType(
    const morphac::math::numeric::IntegratorType& integrator_type,
    morphac::mechanics::models::KinematicModel& kinematic_model);

}  // namespace utils
}  // namespace morphac

#endif
