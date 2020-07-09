#include "simulation/playground/binding/include/playground_spec_binding.h"

namespace morphac {
namespace simulation {
namespace playground {
namespace binding {

namespace py = pybind11;

using std::string;

using morphac::simulation::playground::PlaygroundSpec;

void define_playground_spec_binding(py::module& m) {
  py::class_<PlaygroundSpec> playground_spec(m, "PlaygroundSpec");

  playground_spec.def(
      py::init<const string, const double, const int, const int>(),
      py::arg("name"), py::arg("dt"), py::arg("gui_width"),
      py::arg("gui_height"));
  playground_spec.def_readonly("name", &PlaygroundSpec::name);
  playground_spec.def_readonly("dt", &PlaygroundSpec::dt);
  playground_spec.def_readonly("gui_width", &PlaygroundSpec::gui_width);
  playground_spec.def_readonly("gui_height", &PlaygroundSpec::gui_height);
}

}  // namespace binding
}  // namespace playground
}  // namespace simulation
}  // namespace morphac
