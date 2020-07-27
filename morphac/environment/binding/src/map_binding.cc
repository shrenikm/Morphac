#include "environment/binding/include/map_binding.h"

namespace morphac {
namespace environment {
namespace binding {

namespace py = pybind11;

using Eigen::MatrixXd;
using morphac::environment::Map;

void define_map_binding(py::module& m) {
  py::class_<Map> map(m, "Map");

  map.def(py::init<const double, const double, const double>(),
                  py::arg("width"), py::arg("height"), py::arg("resolution"));
  map.def(py::init<const MatrixXd&, const double>(), py::arg("data"),
                  py::arg("resolution"));
  map.def_property_readonly("width", &Map::get_width);
  map.def_property_readonly("height", &Map::get_height);
  map.def_property_readonly("resolution", &Map::get_resolution);
  map.def_property("data", &Map::get_data,
                           &Map::set_data);
}

}  // namespace binding
}  // namespace environment
}  // namespace morphac
