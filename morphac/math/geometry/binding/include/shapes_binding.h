#ifndef SHAPES_BINDING_H
#define SHAPES_BINDING_H

#include "math/geometry/include/shapes.h"
#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"

namespace morphac {
namespace math {
namespace geometry {
namespace binding {

void define_shapes_binding(pybind11::module& m);

}  // namespace binding
}  // namespace geometry
}  // namespace math
}  // namespace morphac

#endif