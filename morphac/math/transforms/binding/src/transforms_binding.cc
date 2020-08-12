#include "math/transforms/binding/include/transforms_binding.h"

namespace morphac {
namespace math {
namespace transforms {
namespace binding {

namespace py = pybind11;

using Eigen::Vector2d;

using morphac::constructs::Coordinate;
using morphac::math::transforms::RotationMatrix;
using morphac::math::transforms::TransformationMatrix;
using morphac::math::transforms::CanvasToWorld;
using morphac::math::transforms::WorldToCanvas;

void define_transforms_binding(py::module& m) {
  m.def("rotation_matrix", &RotationMatrix, py::arg("angle"));
  m.def("transformation_matrix",
        py::overload_cast<const double, const Vector2d&>(&TransformationMatrix),
        py::arg("angle"), py::arg("translation"));
  m.def(
      "transformation_matrix",
      py::overload_cast<const double, const Coordinate&>(&TransformationMatrix),
      py::arg("angle"), py::arg("translation"));
  m.def("canvas_to_world",
        py::overload_cast<const Vector2d&, const double>(&CanvasToWorld),
        py::arg("canvas_coord"), py::arg("resolution"));
  m.def("canvas_to_world",
        py::overload_cast<const Coordinate&, const double>(&CanvasToWorld),
        py::arg("canvas_coord"), py::arg("resolution"));
  m.def(
      "world_to_canvas",
      py::overload_cast<const Vector2d&, const double, const std::vector<int>&>(
          &WorldToCanvas),
      py::arg("world_coord"), py::arg("resolution"), py::arg("canvas_size"));
  m.def("world_to_canvas",
        py::overload_cast<const Coordinate&, const double,
                          const std::vector<int>&>(&WorldToCanvas),
        py::arg("world_coord"), py::arg("resolution"), py::arg("canvas_size"));
}

}  // namespace binding
}  // namespace transforms
}  // namespace math
}  // namespace morphac
