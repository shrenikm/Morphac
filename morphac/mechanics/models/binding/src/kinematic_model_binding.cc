#include "mechanics/models/binding/include/kinematic_model_binding.h"

namespace morphac {
namespace mechanics {
namespace models {
namespace binding {

namespace py = pybind11;

using std::string;

void define_kinematic_model_binding(py::module& m) {
  py::class_<KinematicModel, PyKinematicModel> kinematic_model(
      m, "KinematicModel");
  kinematic_model.def(
      py::init<const string, const int, const int, const int>());
  kinematic_model.def("ComputeStateDerivative",
                      &KinematicModel::ComputeStateDerivative);
}

}  // namespace binding
}  // namespace models
}  // namespace mechanics
}  // namespace morphac
