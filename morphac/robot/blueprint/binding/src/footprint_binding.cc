#include "robot/blueprint/binding/include/footprint_binding.h"

namespace morphac {
namespace robot {
namespace blueprint {
namespace binding {

namespace py = pybind11;

using Eigen::MatrixXd;

using morphac::robot::blueprint::Footprint;

void define_footprint_binding(py::module& m) {
  py::class_<Footprint> footprint(m, "Footprint");

  footprint.def(py::init<const MatrixXd>(), py::arg("data"));
  footprint.def_property_readonly("data", &Footprint::get_footprint_matrix);
}

}  // namespace binding
}  // namespace blueprint
}  // namespace robot
}  // namespace morphac

