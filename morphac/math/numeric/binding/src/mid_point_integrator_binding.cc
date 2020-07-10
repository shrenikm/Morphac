#include "math/numeric/binding/include/mid_point_integrator_binding.h"

namespace morphac {
namespace math {
namespace numeric {
namespace binding {

namespace py = pybind11;

using morphac::math::numeric::Integrator;
using morphac::math::numeric::MidPointIntegrator;
using morphac::mechanics::models::KinematicModel;

void define_mid_point_integrator_binding(py::module& m) {
  py::class_<MidPointIntegrator, Integrator> mid_point_integrator(
      m, "MidPointIntegrator");

  mid_point_integrator.def(py::init<KinematicModel&>(),
                           py::arg("kinematic_model"), py::keep_alive<1, 2>());
  mid_point_integrator.def("step", &MidPointIntegrator::Step,
                           py::arg("robot_state"), py::arg("control_input"),
                           py::arg("dt"));
  mid_point_integrator.def("integrate", &MidPointIntegrator::Integrate,
                           py::arg("robot_state"), py::arg("control_input"),
                           py::arg("time"), py::arg("dt"));
}

}  // namespace binding
}  // namespace numeric
}  // namespace math
}  // namespace morphac
