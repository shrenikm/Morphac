#include "math/transforms/binding/include/transforms_binding.h"

namespace morphac {
namespace math {
namespace transforms {
namespace binding {

namespace py = pybind11;

using std::vector;

using morphac::common::aliases::Pixel;
using morphac::common::aliases::Pixels;
using morphac::common::aliases::Point;
using morphac::common::aliases::Points;
using morphac::math::transforms::CanvasToWorld;
using morphac::math::transforms::RotatePoints;
using morphac::math::transforms::RotationMatrix;
using morphac::math::transforms::TransformationMatrix;
using morphac::math::transforms::TransformPoints;
using morphac::math::transforms::TranslatePoints;
using morphac::math::transforms::WorldToCanvas;

void define_transforms_binding(py::module& m) {
  m.def("rotation_matrix", &RotationMatrix, py::arg("angle"));
  m.def("transformation_matrix", &TransformationMatrix, py::arg("angle"),
        py::arg("translation"));

  m.def("translate_points", &TranslatePoints, py::arg("points"),
        py::arg("translation"));
  m.def("rotate_points", &RotatePoints, py::arg("points"), py::arg("angle"),
        py::arg("center") = Point::Zero());
  m.def("transform_points", &TransformPoints, py::arg("points"),
        py::arg("angle"), py::arg("translation"));

  // Cpp overloads.
  m.def("canvas_to_world",
        py::overload_cast<const Pixel&, const double, const vector<int>&>(
            &CanvasToWorld),
        py::arg("canvas_coord"), py::arg("resolution"), py::arg("canvas_size"));
  m.def("canvas_to_world",
        py::overload_cast<const Pixels&, const double, const vector<int>&>(
            &CanvasToWorld),
        py::arg("canvas_coords"), py::arg("resolution"),
        py::arg("canvas_size"));

  // Cpp overloads + default value overloads for python.
  m.def("world_to_canvas",
        py::overload_cast<const Point&, const double, const vector<int>&>(
            &WorldToCanvas),
        py::arg("world_coord"), py::arg("resolution"), py::arg("canvas_size"));
  m.def("world_to_canvas",
        py::overload_cast<const Points&, const double, const vector<int>&>(
            &WorldToCanvas),
        py::arg("world_coords"), py::arg("resolution"), py::arg("canvas_size"));
}

}  // namespace binding
}  // namespace transforms
}  // namespace math
}  // namespace morphac
