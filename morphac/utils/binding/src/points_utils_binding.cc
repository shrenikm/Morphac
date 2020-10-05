#include "utils/binding/include/points_utils_binding.h"

namespace morphac {
namespace utils {
namespace binding {

namespace py = pybind11;

using morphac::utils::HomogenizePoints;
using morphac::utils::UnHomogenizePoints;

void define_points_utils_binding(py::module& m) {
  m.def("homogenize_points", &HomogenizePoints, py::arg("points"));
  m.def("unhomogenize_points", &UnHomogenizePoints,
        py::arg("homogeneous_points"));
}

}  // namespace binding
}  // namespace utils
}  // namespace morphac
