#include "robot/blueprint/binding/include/footprint_binding.h"

namespace morphac {
namespace robot {
namespace blueprint {
namespace binding {

namespace py = pybind11;

using Eigen::MatrixXd;
using Eigen::Vector2d;

using morphac::robot::blueprint::Footprint;

void define_footprint_binding(py::module& m) {
  py::class_<Footprint> footprint(m, "Footprint");

  footprint.def(py::init<const MatrixXd>(), py::arg("data"));
  footprint.def_property_readonly("data", &Footprint::get_data);
  footprint.def_static("create_circular_footprint",
                       &Footprint::CreateCircularFootprint, py::arg("radius"),
                       py::arg("angular_resolution"),
                       py::arg("relative_center") = Vector2d::Zero());
  footprint.def_static("create_rectangular_footprint",
                       &Footprint::CreateRectangularFootprint,
                       py::arg("size_x"), py::arg("size_y"), py::arg("angle"),
                       py::arg("relative_center") = Vector2d::Zero());
  footprint.def_static("create_rounded_rectangular_footprint",
                       &Footprint::CreateRoundedRectangularFootprint,
                       py::arg("size_x"), py::arg("size_y"), py::arg("angle"),
                       py::arg("radius"), py::arg("angular_resolution"),
                       py::arg("relative_center") = Vector2d::Zero());
  footprint.def_static("create_triangular_footprint",
                       &Footprint::CreateTriangularFootprint, py::arg("base"),
                       py::arg("height"), py::arg("angle"),
                       py::arg("relative_center") = Vector2d::Zero());
}

}  // namespace binding
}  // namespace blueprint
}  // namespace robot
}  // namespace morphac
