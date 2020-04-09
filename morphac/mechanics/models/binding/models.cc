#include "pybind11/eigen.h"
#include "pybind11/operators.h"
#include "pybind11/pybind11.h"

// include "mechanics/models/binding/include/diffdrive_model_binding.h"
// include "mechanics/models/binding/include/dubin_model_binding.h"
// include "mechanics/models/binding/include/kinematic_model_binding.h"
// include "mechanics/models/binding/include/tricycle_model_binding.h"

#include "mechanics/models/include/diffdrive_model.h"
#include "mechanics/models/include/kinematic_model.h"

namespace morphac {
namespace mechanics {
namespace models {
namespace binding {

namespace py = pybind11;

using std::string;
using morphac::mechanics::models::KinematicModel;
using morphac::mechanics::models::DiffDriveModel;

// Trampoline class as the kinematic model class is abstract.
class PyKinematicModel : public morphac::mechanics::models::KinematicModel {
 public:
  using KinematicModel::KinematicModel;

  morphac::constructs::State ComputeStateDerivative(
      const morphac::constructs::State& state,
      const morphac::constructs::ControlInput& input) const override {
    PYBIND11_OVERLOAD_PURE_NAME(morphac::constructs::State, KinematicModel,
                                "compute_state_derivative",
                                ComputeStateDerivative, state, input);
  }
};

PYBIND11_MODULE(_binding_models, m) {
  // define_kinematic_model_binding(m);
  // define_diffdrive_model_binding(m);

  py::class_<KinematicModel, PyKinematicModel> kinematic_model(
      m, "KinematicModel");
  kinematic_model.def(py::init<const string, const int, const int, const int>(),
                      py::arg("name"), py::arg("size_pose"),
                      py::arg("size_velocity"), py::arg("size_input"));
  kinematic_model.def("compute_state_derivative",
                      &KinematicModel::ComputeStateDerivative);
  kinematic_model.def_readonly("name", &KinematicModel::name);
  kinematic_model.def_readonly("size_pose", &KinematicModel::size_pose);
  kinematic_model.def_readonly("size_velocity", &KinematicModel::size_velocity);
  kinematic_model.def_readonly("size_input", &KinematicModel::size_input);

  py::class_<DiffDriveModel, KinematicModel> diffdrive_model(m,
                                                             "DiffDriveModel");
  diffdrive_model.def(py::init<const string, const double, const double>(),
                      py::arg("name"), py::arg("radius"), py::arg("length"));
  diffdrive_model.def("compute_state_derivative",
                      &DiffDriveModel::ComputeStateDerivative);
  diffdrive_model.def_readonly("name", &DiffDriveModel::name);
  diffdrive_model.def_readonly("radius", &DiffDriveModel::radius);
  diffdrive_model.def_readonly("length", &DiffDriveModel::length);
  diffdrive_model.def_readonly("size_pose", &KinematicModel::size_pose);
  diffdrive_model.def_readonly("size_velocity", &KinematicModel::size_velocity);
  diffdrive_model.def_readonly("size_input", &KinematicModel::size_input);
}

}  // namespace binding
}  // namespace models
}  // namespace mechanics
}  // namespace morphac
