#include "utils/include/geometry_utils.h"

namespace morphac {
namespace utils {

using std::fabs;

using Eigen::Vector2d;
using Eigen::VectorXd;

using morphac::common::aliases::Points;
using morphac::math::transforms::TransformationMatrix;
using morphac::utils::HomogenizePoints;
using morphac::utils::TransformPoints;
using morphac::utils::UnHomogenizePoints;

Points CreateArc(const double start_angle, const double end_angle,
                 const double radius, const double angular_resolution,
                 const Vector2d& center) {
  MORPH_REQUIRE(radius >= 0, std::invalid_argument,
                "Radius must be non-negative.");
  // We have num_points * angular_resolution = 2 * pi (360 degrees).
  int num_points =
      std::round(fabs(end_angle - start_angle) / angular_resolution);

  Points arc(num_points, 2);

  VectorXd angles = VectorXd::LinSpaced(num_points, start_angle, end_angle);

  VectorXd x_coordinates = radius * Eigen::cos(angles.array()).matrix();
  VectorXd y_coordinates = radius * Eigen::sin(angles.array()).matrix();

  arc.col(0) = x_coordinates;
  arc.col(1) = y_coordinates;

  return TransformPoints(arc, 0., center);
}

Points CreateCircularPolygon(const double radius,
                             const double angular_resolution,
                             const Vector2d& center) {
  MORPH_REQUIRE(radius >= 0, std::invalid_argument,
                "Radius must be non-negative.");
  // A circle is basically an arc from 0 to 2 * pi. We make sure that both 0 and
  // 2 * pi isn't included as we don't want duplicate corners in the polygon.
  return CreateArc(0., 2 * M_PI - angular_resolution, radius,
                   angular_resolution, center);
}

Points CreateRectangularPolygon(const double size_x, const double size_y,
                                const double angle, const Vector2d& center) {
  // The reason the conditions are >= 0 and not > 0 is because sometimes
  // CreateRoundedRectangularPolygon may call this function with a zero size.
  MORPH_REQUIRE(size_x >= 0, std::invalid_argument,
                "Size along the x axis must be non-negative.");
  MORPH_REQUIRE(size_y >= 0, std::invalid_argument,
                "Size along the y axis must be non-negative.");

  Points polygon(4, 2);
  polygon << -size_x / 2, size_y / 2, size_x / 2, size_y / 2, size_x / 2,
      -size_y / 2, -size_x / 2, -size_y / 2;

  return TransformPoints(polygon, angle, center);
}

Points CreateRoundedRectangularPolygon(const double size_x, const double size_y,
                                       const double angle, const double radius,
                                       const double angular_resolution,
                                       const Vector2d& center) {
  // The reason the conditosn are >= 0 and not > 0 is that there might be times
  // when 0. sizes are required. See the comment in CreateRectangularPolygon.
  MORPH_REQUIRE(size_x >= 0, std::invalid_argument,
                "Size along the x axis must be non-negative.");
  MORPH_REQUIRE(size_y >= 0, std::invalid_argument,
                "Size along the y axis must be non-negative.");
  MORPH_REQUIRE(radius >= 0, std::invalid_argument,
                "Radius must be non-negative.");
  MORPH_REQUIRE(radius <= (size_x / 2) && radius <= (size_y / 2),
                std::invalid_argument,
                "The radius is too large compared to the rectangle sizes.");
  // The rounded rectangle is basically just the four arcs that form the
  // corners of the shape.

  // Computing the centers of the arcs. This is basically the corners of a
  // rectangle with sizes - 2 * radius.
  Points centers = CreateRectangularPolygon(
      size_x - 2 * radius, size_y - 2 * radius, 0, Vector2d::Zero());

  Points arc1 = CreateArc(M_PI, M_PI / 2, radius, angular_resolution,
                          centers.row(0).transpose());
  Points arc2 = CreateArc(M_PI / 2, 0, radius, angular_resolution,
                          centers.row(1).transpose());
  Points arc3 = CreateArc(0, -M_PI / 2, radius, angular_resolution,
                          centers.row(2).transpose());
  Points arc4 = CreateArc(-M_PI / 2, -M_PI, radius, angular_resolution,
                          centers.row(3).transpose());

  Points polygon(arc1.rows() + arc2.rows() + arc3.rows() + arc4.rows(), 2);
  polygon << arc1, arc2, arc3, arc4;

  return TransformPoints(polygon, angle, center);
}

}  // namespace utils
}  // namespace morphac
