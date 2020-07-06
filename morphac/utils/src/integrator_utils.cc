#include "utils/include/integrator_utils.h"

namespace morphac {
namespace utils {

using std::unique_ptr;
using std::make_unique;

using morphac::math::numeric::Integrator;
using morphac::math::numeric::IntegratorType;
using morphac::math::numeric::EulerIntegrator;
using morphac::math::numeric::MidPointIntegrator;
using morphac::math::numeric::RK4Integrator;
using morphac::mechanics::models::KinematicModel;

unique_ptr<Integrator> IntegratorFromType(const IntegratorType& integrator_type,
                                          KinematicModel& kinematic_model) {
  switch (integrator_type) {
    case IntegratorType::kEulerIntegrator:
      return std::move(make_unique<EulerIntegrator>(kinematic_model));
    case IntegratorType::kMidPointIntegrator:
      return std::move(make_unique<MidPointIntegrator>(kinematic_model));
    case IntegratorType::kRK4Integrator:
      return std::move(make_unique<RK4Integrator>(kinematic_model));
    default:
      MORPH_THROW(std::invalid_argument,
                  "Integrator type does not match any of the defined types.");
  }
}

}  // namespace utils
}  // namespace morphac

