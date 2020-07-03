#include "simulation/binding/include/playground_state_binding.h"

namespace morphac {
namespace simulation {
namespace binding {

namespace py = pybind11;

using morphac::environment::Map;

void define_playground_state_binding(py::module& m) {
  py::class_<PlaygroundState> playground_state(m, "PlaygroundState");

  playground_state.def(py::init<const Map&>(), py::arg("map"));
  playground_state.def_property("map", &PlaygroundState::get_map,
                                &PlaygroundState::set_map);
  playground_state.def_property_readonly("robot_oracle",
                                         &PlaygroundState::get_robot_oracle);
  playground_state.def("get_robot", &PlaygroundState::get_robot,
                       py::arg("uid"));
  playground_state.def_property("robot_state",
                                &PlaygroundState::get_robot_state,
                                &PlaygroundState::set_robot_state);
}

}  // namespace binding
}  // namespace simulation
}  // namespace morphac
