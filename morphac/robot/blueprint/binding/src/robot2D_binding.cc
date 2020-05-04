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

  // As the kinematic model is a reference (Even in the class), we need to
  // keep it alive until the Robot2D object is deleted. Hence we use keep_alive
  // and tie its lifetime to the Robot2D object. If this is not done, we would
  // not be able to construct a Robot2D object using:
  // r = Robot2D("name", KinematicModel(args), footprint)
  // As the kinematic model object is temporary, gets deleted and the cpp side
  // throws a segfault.
  robot2D.def(py::init<const string, KinematicModel&, const Footprint2D&>(),
              py::arg("name"), py::arg("kinematic_model"), py::arg("footprint"),
              py::keep_alive<1, 3>());
  robot2D.def(py::init<const string, KinematicModel&, const Footprint2D&,
                       const State&>(),
              py::arg("name"), py::arg("kinematic_model"), py::arg("footprint"),
              py::arg("initial_state"), py::keep_alive<1, 3>());
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
  robot2D.def_property("state", &Robot2D::get_state, &Robot2D::set_state);
  robot2D.def_property("pose", &Robot2D::get_pose, &Robot2D::set_pose);
  robot2D.def_property("velocity", &Robot2D::get_velocity,
                       &Robot2D::set_velocity);
}

}  // namespace binding
}  // namespace blueprint
}  // namespace robot
}  // namespace morphac
