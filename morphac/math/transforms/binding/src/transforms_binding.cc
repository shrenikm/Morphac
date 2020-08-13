#include "math/transforms/binding/include/transforms_binding.h"

namespace morphac {
namespace math {
namespace transforms {
namespace binding {

namespace py = pybind11;

using Eigen::Vector2d;
using Eigen::Vector2i;

using morphac::math::transforms::RotationMatrix;
using morphac::math::transforms::TransformationMatrix;
using morphac::math::transforms::CanvasToWorld;
using morphac::math::transforms::WorldToCanvas;

void define_transforms_binding(py::module& m) {
  m.def("rotation_matrix", &RotationMatrix, py::arg("angle"));
  m.def("transformation_matrix", &TransformationMatrix, py::arg("angle"),
        py::arg("translation"));
  m.def("canvas_to_world", &CanvasToWorld, py::arg("canvas_coord"),
        py::arg("resolution"));
  m.def("world_to_canvas", &WorldToCanvas, py::arg("world_coord"),
        py::arg("resolution"), py::arg("canvas_size"));
  m.def("world_to_canvas",
        [](const Vector2d& world_coord, const double resolution) {
          return WorldToCanvas(world_coord, resolution);
        }, py::arg("world_coord"), py::arg("resolution"));
}

}  // namespace binding
}  // namespace transforms
}  // namespace math
}  // namespace morphac
