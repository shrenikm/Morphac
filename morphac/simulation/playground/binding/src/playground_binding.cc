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
  playground.def_property_readonly("spec", &Playground::get_spec);
  playground.def_property_readonly("state", &Playground::get_state,
                                   py::return_value_policy::reference);
  playground.def("get_pilot_oracle", &Playground::get_pilot_oracle);
  // Careful while using the python bindings as both the get_pilot and
  // get_integrator functions return references. This is because the
  // integrator is non copyable as it is a dereferenced unique_ptr and the
  // pilot object could potentially be non-copyable.
  playground.def("get_pilot", &Playground::get_pilot, py::arg("uid"),
                 py::return_value_policy::reference);
  playground.def("get_integrator", &Playground::get_integrator, py::arg("uid"),
                 py::return_value_policy::reference);
  playground.def("add_robot", &Playground::AddRobot, py::arg("robot"),
                 py::arg("pilot"), py::arg("integrator_type"), py::arg("uid"), py::keep_alive<1, 2>(), py::keep_alive<1, 3>());
}

}  // namespace binding
}  // namespace playground
}  // namespace simulation
}  // namespace morphac
