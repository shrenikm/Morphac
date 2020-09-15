#ifndef TRANSFORMS_BINDING_H
#define TRANSFORMS_BINDING_H

#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include "constructs/include/coordinate.h"
#include "math/transforms/include/transforms.h"

namespace morphac {
namespace math {
namespace transforms {
namespace binding {

void define_transforms_binding(pybind11::module& m);

}  // namespace binding
}  // namespace transforms
}  // namespace math
}  // namespace morphac

#endif
