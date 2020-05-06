#include "math/numeric/binding/include/euler_integrator_binding.h"

namespace morphac {
namespace math {
namespace numeric {
namespace binding {

namespace py = pybind11;

using morphac::math::numeric::EulerIntegrator;
using morphac::math::numeric::Integrator;
using morphac::mechanics::models::KinematicModel;

void define_euler_integrator_binding(py::module& m) {
  py::class_<EulerIntegrator, Integrator> euler_integrator(m,
                                                           "EulerIntegrator");

  euler_integrator.def(py::init<KinematicModel&>(), py::arg("kinematic_model"),
                       py::keep_alive<1, 2>());
  euler_integrator.def("step", &EulerIntegrator::Step, py::arg("state"),
                       py::arg("input"), py::arg("dt"));
  euler_integrator.def("integrate", &EulerIntegrator::Integrate,
                       py::arg("state"), py::arg("input"), py::arg("time"),
                       py::arg("dt"));
}

}  // namespace binding
}  // namespace numeric
}  // namespace math
}  // namespace morphac
