#include "utils/binding/include/transforms_utils_binding.h"

namespace morphac {
namespace utils {
namespace binding {

namespace py = pybind11;

using Eigen::Vector2d;

using morphac::utils::HomogenizePoints;
using morphac::utils::UnHomogenizePoints;
using morphac::utils::TranslatePoints;
using morphac::utils::RotatePoints;
using morphac::utils::TransformPoints;

void define_transforms_utils_binding(py::module& m) {
  m.def("homogenize_points", &HomogenizePoints, py::arg("points"));
  m.def("unhomogenize_points", &UnHomogenizePoints,
        py::arg("homogeneous_points"));
  m.def("translate_points", &TranslatePoints, py::arg("points"),
        py::arg("translation"));
  m.def("rotate_points", &RotatePoints, py::arg("points"), py::arg("angle"),
        py::arg("center") = Vector2d::Zero());
  m.def("transform_points", &TransformPoints, py::arg("points"),
        py::arg("angle"), py::arg("translation"));
}

}  // namespace binding
}  // namespace utils
}  // namespace morphac
