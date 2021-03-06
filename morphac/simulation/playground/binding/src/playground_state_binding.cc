#include "simulation/playground/binding/include/playground_state_binding.h"

namespace morphac {
namespace simulation {
namespace playground {
namespace binding {

namespace py = pybind11;

using morphac::environment::Map;

using morphac::simulation::playground::PlaygroundState;

void define_playground_state_binding(py::module& m) {
  py::class_<PlaygroundState> playground_state(m, "PlaygroundState");

  playground_state.def(py::init<const Map&>(), py::arg("map"));
  playground_state.def_property("time", &PlaygroundState::get_time,
                                &PlaygroundState::set_time);
  playground_state.def_property("map", &PlaygroundState::get_map,
                                &PlaygroundState::set_map);
  playground_state.def_property_readonly("robot_oracle",
                                         &PlaygroundState::get_robot_oracle);
  playground_state.def("get_robot", &PlaygroundState::get_robot,
                       py::arg("uid"));
  playground_state.def("get_robot_state", &PlaygroundState::get_robot_state,
                       py::arg("uid"));
  playground_state.def("set_robot_state", &PlaygroundState::set_robot_state,
                       py::arg("state"), py::arg("uid"));
  playground_state.def_property_readonly("num_robots",
                                         &PlaygroundState::NumRobots);
  playground_state.def("add_robot", &PlaygroundState::AddRobot,
                       py::arg("robot"), py::arg("uid"),
                       py::keep_alive<0, 2>());
}

}  // namespace binding
}  // namespace playground
}  // namespace simulation
}  // namespace morphac
