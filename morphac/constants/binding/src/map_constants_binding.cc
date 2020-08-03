#include "constants/binding/include/map_constants_binding.h"

namespace morphac {
namespace constants {
namespace binding {

namespace py = pybind11;

using morphac::constants::MapConstants;

void define_map_constants_binding(py::module& m) {
  py::class_<MapConstants> map_constants(m, "MapConstants");
  map_constants.def_readonly_static("EMPTY", &MapConstants::EMPTY);
  map_constants.def_readonly_static("OBSTACLE", &MapConstants::OBSTACLE);
}

}  // namespace binding
}  // namespace constants
}  // namespace morphac
