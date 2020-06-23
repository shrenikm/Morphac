#include "math/numeric/binding/include/integrator_binding.h"

namespace morphac {
namespace math {
namespace numeric {
namespace binding {

namespace py = pybind11;

using morphac::math::numeric::Integrator;
using morphac::math::numeric::IntegratorType;
using morphac::mechanics::models::KinematicModel;

void define_integrator_binding(py::module& m) {
  py::class_<Integrator, PyIntegrator> integrator(m, "Integrator");

  integrator.def(py::init<KinematicModel&>(), py::arg("kinematic_model"),
                 py::keep_alive<1, 2>());
  integrator.def("step", &Integrator::Step, py::arg("robot_state"),
                 py::arg("robot_input"), py::arg("dt"));
  integrator.def("integrate", &Integrator::Integrate, py::arg("robot_state"),
                 py::arg("robot_input"), py::arg("time"), py::arg("dt"));
}

void define_integrator_type_binding(py::module& m) {
  py::enum_<IntegratorType> integrator_type(m, "IntegratorType");
  integrator_type.value("EULER_INTEGRATOR", IntegratorType::kEulerIntegrator);
  integrator_type.value("MID_POINT_INTEGRATOR",
                        IntegratorType::kMidPointIntegrator);
  integrator_type.value("RK4_INTEGRATOR", IntegratorType::kRK4Integrator);
}

}  // namespace binding
}  // namespace numeric
}  // namespace math
}  // namespace morphac
