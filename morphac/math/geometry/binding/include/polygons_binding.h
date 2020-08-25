#ifndef POLYGONS_BINDING_H
#define POLYGONS_BINDING_H

#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"

#include "math/geometry/include/polygons.h"

namespace morphac {
namespace math {
namespace geometry {
namespace binding {

void define_polygons_binding(pybind11::module& m);

}  // namespace binding
}  // namespace geometry
}  // namespace math
}  // namespace morphac

#endif
