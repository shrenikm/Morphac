#include "robot/blueprint/binding/include/footprint2D_binding.h"

namespace morphac {
namespace robot {
namespace blueprint {
namespace binding {

namespace py = pybind11;

using Eigen::MatrixXd;

using morphac::robot::blueprint::Footprint2D;

void define_footprint2D_binding(py::module& m) {
  py::class_<Footprint2D> footprint2D(m, "Footprint2D");

  footprint2D.def(py::init<const MatrixXd>(), py::arg("data"));
  footprint2D.def_property_readonly("data", &Footprint2D::get_footprint_matrix);
}

}  // namespace binding
}  // namespace blueprint
}  // namespace robot
}  // namespace morphac

