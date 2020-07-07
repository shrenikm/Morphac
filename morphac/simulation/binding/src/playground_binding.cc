#include "simulation/binding/include/playground_binding.h"

namespace morphac {
namespace simulation {
namespace binding {

namespace py = pybind11;

using morphac::environment::Map;
using morphac::simulation::PlaygroundSpec;

void define_playground_binding(py::module& m) {
  py::class_<Playground> playground(m, "Playground");

  playground.def(py::init<const PlaygroundSpec&, const Map&>(),
                 py::arg("playground_spec"), py::arg("map"));
  playground.def_property_readonly("state", &Playground::get_state);
  playground.def("add_robot", &Playground::AddRobot, py::arg("robot"),
                 py::arg("pilot"), py::arg("integrator_type"), py::arg("uid"));
  playground.def("execute", &Playground::Execute);
}

}  // namespace binding
}  // namespace simulation
}  // namespace morphac
