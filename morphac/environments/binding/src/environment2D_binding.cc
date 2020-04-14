#include "environments/binding/include/environment2D_binding.h"

namespace morphac {
namespace environments {
namespace binding {

namespace py = pybind11;

using Eigen::MatrixXd;
using morphac::environments::Environment2D;

void define_environment2D_binding(py::module& m) {
  py::class_<Environment2D> environment2D(m, "Environment2D");

  environment2D.def(py::init<const double, const double, const double>(),
                    py::arg("width"), py::arg("height"), py::arg("resolution"));
  environment2D.def(py::init<const MatrixXd&, const double>(), py::arg("data"),
                    py::arg("resolution"));
  environment2D.def_property_readonly("width", &Environment2D::get_width);
  environment2D.def_property_readonly("height", &Environment2D::get_height);
  environment2D.def_property_readonly("resolution",
                                      &Environment2D::get_resolution);
  // map is mapped to data in python to keep it consistent and pythonic.
  environment2D.def_property("data", &Environment2D::get_map,
                             &Environment2D::set_map);
}

}  // namespace binding
}  // namespace environments
}  // namespace morphac
