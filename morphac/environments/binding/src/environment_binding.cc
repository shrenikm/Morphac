#include "environments/binding/include/environment_binding.h"

namespace morphac {
namespace environments {
namespace binding {

namespace py = pybind11;

using Eigen::MatrixXd;
using morphac::environments::Environment;

void define_environment_binding(py::module& m) {
  py::class_<Environment> environment(m, "Environment");

  environment.def(py::init<const double, const double, const double>(),
                  py::arg("width"), py::arg("height"), py::arg("resolution"));
  environment.def(py::init<const MatrixXd&, const double>(), py::arg("data"),
                  py::arg("resolution"));
  environment.def_property_readonly("width", &Environment::get_width);
  environment.def_property_readonly("height", &Environment::get_height);
  environment.def_property_readonly("resolution", &Environment::get_resolution);
  // map is mapped to data in python to keep it consistent and pythonic.
  environment.def_property("data", &Environment::get_map,
                           &Environment::set_map);
}

}  // namespace binding
}  // namespace environments
}  // namespace morphac
