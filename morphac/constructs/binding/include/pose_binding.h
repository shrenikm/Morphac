#include "pybind11/eigen.h"
#include "pybind11/operators.h"
#include "pybind11/pybind11.h"

#include "constructs/include/pose.h"

namespace morphac {
namespace constructs {
namespace binding {

void define_pose_binding(pybind11::module& m);

}  // namespace binding
}  // namespace constructs
}  // namespace morphac

