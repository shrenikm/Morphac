#include "utils/binding/include/numeric_utils_binding.h"

namespace morphac {
namespace utils {
namespace binding {

namespace py = pybind11;

using morphac::utils::IsEqual;

void define_numeric_utils_binding(py::module& m) {
  m.def("is_equal", &IsEqual, py::arg("value1"), py::arg("value2"),
        py::arg("absolute_tolerance") = 1e-7,
        py::arg("relative_tolerance") = 1e-7);
}

}  // namespace binding
}  // namespace utils
}  // namespace morphac
