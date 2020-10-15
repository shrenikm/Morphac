#include "robot/blueprint/binding/include/footprint_binding.h"

namespace morphac {
namespace robot {
namespace blueprint {
namespace binding {

namespace py = pybind11;

using Eigen::MatrixXd;

using morphac::common::aliases::Point;
using morphac::robot::blueprint::Footprint;

void define_footprint_binding(py::module& m) {
  py::class_<Footprint> footprint(m, "Footprint");

  footprint.def(py::init<const MatrixXd>(), py::arg("data"));
  footprint.def_property_readonly("data", &Footprint::get_data);
  footprint.def_property_readonly("bounding_box", &Footprint::get_bounding_box);
  footprint.def_static("create_circular_footprint",
                       &Footprint::CreateCircularFootprint,
                       py::arg("circle_shape"), py::arg("angular_resolution"));
  footprint.def_static("create_rectangular_footprint",
                       &Footprint::CreateRectangularFootprint,
                       py::arg("rectangle_shape"));
  footprint.def_static("create_rounded_rectangular_footprint",
                       &Footprint::CreateRoundedRectangularFootprint,
                       py::arg("rounded_rectangle_shape"),
                       py::arg("angular_resolution"));
  footprint.def_static("create_triangular_footprint",
                       &Footprint::CreateTriangularFootprint,
                       py::arg("triangle_shape"));
}

}  // namespace binding
}  // namespace blueprint
}  // namespace robot
}  // namespace morphac
