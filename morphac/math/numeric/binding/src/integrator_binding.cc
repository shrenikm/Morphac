#include "math/numeric/binding/include/integrator_binding.h"

namespace morphac {
namespace math {
namespace numeric {
namespace binding {

namespace py = pybind11;

using morphac::math::numeric::Integrator;
using morphac::mechanics::models::KinematicModel;

void define_integrator_binding(py::module& m) {
  py::class_<Integrator, PyIntegrator> integrator(m, "Integrator");

  integrator.def(py::init<KinematicModel&>(), py::arg("kinematic_model"),
                 py::keep_alive<1, 2>());
  integrator.def("step", &Integrator::Step);
  integrator.def("integrate", &Integrator::Integrate);
}

}  // namespace binding
}  // namespace numeric
}  // namespace math
}  // namespace morphac