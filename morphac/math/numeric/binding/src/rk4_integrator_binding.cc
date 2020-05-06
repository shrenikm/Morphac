#include "math/numeric/binding/include/rk4_integrator_binding.h"

namespace morphac {
namespace math {
namespace numeric {
namespace binding {

namespace py = pybind11;

using morphac::math::numeric::Integrator;
using morphac::math::numeric::RK4Integrator;
using morphac::mechanics::models::KinematicModel;

void define_rk4_integrator_binding(py::module& m) {
  py::class_<RK4Integrator, Integrator> rk4_integrator(m, "RK4Integrator");

  rk4_integrator.def(py::init<KinematicModel&>(), py::arg("kinematic_model"),
                     py::keep_alive<1, 2>());
  rk4_integrator.def("step", &RK4Integrator::Step, py::arg("state"),
                     py::arg("input"), py::arg("dt"));
  rk4_integrator.def("integrate", &RK4Integrator::Integrate, py::arg("state"),
                     py::arg("input"), py::arg("time"), py::arg("dt"));
}

}  // namespace binding
}  // namespace numeric
}  // namespace math
}  // namespace morphac
