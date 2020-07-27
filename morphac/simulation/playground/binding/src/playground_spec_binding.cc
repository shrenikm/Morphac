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

  playground_spec.def(py::init<const string, const double>(), py::arg("name"),
                      py::arg("dt"));
  playground_spec.def_readonly("name", &PlaygroundSpec::name);
  playground_spec.def_readonly("dt", &PlaygroundSpec::dt);
}

}  // namespace binding
}  // namespace playground
}  // namespace simulation
}  // namespace morphac
