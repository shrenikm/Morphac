#ifndef POLYGONS_H
#define POLYGONS_H

#define _USE_MATH_DEFINES

#include <cmath>

#include "Eigen/Dense"
#include "common/aliases/include/eigen_aliases.h"
#include "common/error_handling/include/error_macros.h"
#include "math/geometry/include/shapes.h"
#include "math/transforms/include/transforms.h"
#include "utils/include/points_utils.h"

namespace morphac {
namespace math {
namespace geometry {

// Polygon creation.
morphac::common::aliases::Points CreateArc(
    const morphac::math::geometry::ArcShape& arc_shape,
    const double angular_resolution);

morphac::common::aliases::Points CreateCircularPolygon(
    const morphac::math::geometry::CircleShape& circle_shape,
    const double angular_resolution);

morphac::common::aliases::Points CreateRectangularPolygon(
    const morphac::math::geometry::RectangleShape& rectangle_shape);

morphac::common::aliases::Points CreateRoundedRectangularPolygon(
    const morphac::math::geometry::RoundedRectangleShape&
        rounded_rectangle_shape,
    const double angular_resolution);

morphac::common::aliases::Points CreateTriangularPolygon(
    const morphac::math::geometry::TriangleShape& triangle_shape);

// Computations with polygons.
morphac::common::aliases::BoundingBox ComputeBoundingBox(
    const morphac::common::aliases::Points& polygon);

// Relationsip between points and polygons.
bool IsPointInsidePolygon(const morphac::common::aliases::Points& polygon,
                          const morphac::common::aliases::Point& point);

bool DoPolygonsIntersect(const morphac::common::aliases::Points& polygon1,
                         const morphac::common::aliases::Points& polygon2);

}  // namespace geometry
}  // namespace math
}  // namespace morphac

#endif
