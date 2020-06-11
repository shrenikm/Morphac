#include "robot/blueprint/binding/include/robot_binding.h"

namespace morphac {
namespace robot {
namespace blueprint {
namespace binding {

namespace py = pybind11;

using std::string;

using morphac::constructs::Input;
using morphac::constructs::State;
using morphac::mechanics::models::KinematicModel;
using morphac::robot::blueprint::Footprint;
using morphac::robot::blueprint::Robot;

void define_robot_binding(py::module& m) {
  py::class_<Robot> robot(m, "Robot");

  // As the kinematic model is a reference (Even in the class), we need to
  // keep it alive until the Robot object is deleted. Hence we use keep_alive
  // and tie its lifetime to the Robot object. If this is not done, we would
  // not be able to construct a Robot object using:
  // r = Robot("name", KinematicModel(args), footprint)
  // As the kinematic model object is temporary, gets deleted and the cpp side
  // throws a segfault.
  robot.def(py::init<const string, KinematicModel&, const Footprint&>(),
            py::arg("name"), py::arg("kinematic_model"), py::arg("footprint"),
            py::keep_alive<1, 3>());
  robot.def(
      py::init<const string, KinematicModel&, const Footprint&, const State&>(),
      py::arg("name"), py::arg("kinematic_model"), py::arg("footprint"),
      py::arg("initial_state"), py::keep_alive<1, 3>());
  robot.def("compute_state_derivative",
            py::overload_cast<const Input&>(&Robot::ComputeStateDerivative,
                                            py::const_),
            py::arg("robot_input"));
  robot.def("compute_state_derivative",
            py::overload_cast<const State&, const Input&>(
                &Robot::ComputeStateDerivative, py::const_),
            py::arg("robot_state"), py::arg("robot_input"));
  robot.def_property_readonly("name", &Robot::get_name);
  robot.def_property_readonly("kinematic_model", &Robot::get_kinematic_model);
  robot.def_property_readonly("footprint", &Robot::get_footprint);
  robot.def_property("state", &Robot::get_state, &Robot::set_state);
  robot.def_property("pose", &Robot::get_pose, &Robot::set_pose);
  robot.def_property("velocity", &Robot::get_velocity, &Robot::set_velocity);
}

}  // namespace binding
}  // namespace blueprint
}  // namespace robot
}  // namespace morphac

