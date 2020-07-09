#include "simulation/playground/binding/include/playground_binding.h"

namespace morphac {
namespace simulation {
namespace playground {
namespace binding {

namespace py = pybind11;

using morphac::environment::Map;
using morphac::simulation::playground::Playground;
using morphac::simulation::playground::PlaygroundSpec;

void define_playground_binding(py::module& m) {
  py::class_<Playground> playground(m, "Playground");

  playground.def(py::init<const PlaygroundSpec&, const Map&>(),
                 py::arg("playground_spec"), py::arg("map"));
  playground.def_property_readonly("state", &Playground::get_state,
                                   py::return_value_policy::reference);
  playground.def("get_pilot", &Playground::get_pilot, py::arg("uid"),
                 py::return_value_policy::reference);
  playground.def("get_integrator", &Playground::get_integrator, py::arg("uid"),
                 py::return_value_policy::reference);
  playground.def("add_robot", &Playground::AddRobot, py::arg("robot"),
                 py::arg("pilot"), py::arg("integrator_type"), py::arg("uid"));
  playground.def("execute", &Playground::Execute);
}

}  // namespace binding
}  // namespace playground
}  // namespace simulation
}  // namespace morphac
