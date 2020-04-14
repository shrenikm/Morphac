#include "robot/blueprint/binding/include/robot2D_binding.h"

namespace morphac {
namespace robot {
namespace blueprint {
namespace binding {

namespace py = pybind11;

using std::string;

using morphac::constructs::Input;
using morphac::constructs::State;
using morphac::mechanics::models::KinematicModel;
using morphac::robot::blueprint::Footprint2D;
using morphac::robot::blueprint::Robot2D;

void define_robot2D_binding(py::module& m) {
  py::class_<Robot2D> robot2D(m, "Robot2D");

  robot2D.def(py::init<const string, KinematicModel&, const Footprint2D&>(),
              py::arg("name"), py::arg("kinematic_model"),
              py::arg("footprint"));
  robot2D.def(py::init<const string, KinematicModel&, const Footprint2D&,
                       const State&>(),
              py::arg("name"), py::arg("kinematic_model"), py::arg("footprint"),
              py::arg("initial_state"));
  robot2D.def("compute_state_derivative",
              py::overload_cast<const Input&>(&Robot2D::ComputeStateDerivative,
                                              py::const_));
  robot2D.def("compute_state_derivative",
              py::overload_cast<const State&, const Input&>(
                  &Robot2D::ComputeStateDerivative, py::const_));
  robot2D.def_property_readonly("name", &Robot2D::get_name);
  robot2D.def_property_readonly("kinematic_model",
                                &Robot2D::get_kinematic_model);
  robot2D.def_property_readonly("footprint", &Robot2D::get_footprint);
  robot2D.def_property_readonly("state", &Robot2D::get_state);
  robot2D.def_property_readonly("pose", &Robot2D::get_pose);
  robot2D.def_property_readonly("velocity", &Robot2D::get_velocity);
}

}  // namespace binding
}  // namespace blueprint
}  // namespace robot
}  // namespace morphac

