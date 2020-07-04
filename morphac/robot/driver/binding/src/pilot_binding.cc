#include "robot/driver/binding/include/pilot_binding.h"

namespace morphac {
namespace robot {
namespace driver {
namespace binding {

namespace py = pybind11;

using morphac::robot::driver::Pilot;

void define_pilot_binding(py::module& m) {
  py::class_<Pilot, PyPilot> pilot(m, "Pilot");

  pilot.def(py::init<>());
  pilot.def("execute", &Pilot::Execute, py::arg("playground_state"),
            py::arg("uid"));
}

}  // namespace binding
}  // namespace driver
}  // namespace robot
}  // namespace morphac
