#include "robot/blueprint/include/footprint.h"

namespace morphac {
namespace robot {
namespace blueprint {

using Eigen::MatrixXd;
using Eigen::Vector2d;
using Eigen::VectorXd;

using morphac::constructs::Coordinate;

Footprint::Footprint(const MatrixXd& data) : data_(data) {
  MORPH_REQUIRE(data.rows() > 0 && data.cols() == 2, std::invalid_argument,
                "Invalid footprint matrix dimensions. Must be n x 2.");
}

const MatrixXd& Footprint::get_data() const { return data_; }

Footprint Footprint::OffsetFootprint(const Footprint& footprint,
                                     const Vector2d& center) {
  // Takes in a zero centered footprint and offsets its points such that the new
  // center is the origin (0, 0).
  return Footprint(footprint.get_data().rowwise() + center.transpose());
}

Footprint Footprint::OffsetFootprint(const Footprint& footprint,
                                     const Coordinate& center) {
  return OffsetFootprint(footprint, center.get_data());
}

Footprint Footprint::CreateRectangularFootprint(const double size_x,
                                                const double size_y,
                                                const Vector2d& center) {
  MatrixXd footprint_data(4, 2);
  footprint_data << -size_x / 2, size_y / 2, size_x / 2, size_y / 2, size_x / 2,
      -size_y / 2, -size_x / 2, -size_y / 2;

  return OffsetFootprint(Footprint(footprint_data), center);
}

Footprint Footprint::CreateRectangularFootprint(const double size_x,
                                                const double size_y,
                                                const Coordinate& center) {
  return CreateRectangularFootprint(size_x, size_y, center.get_data());
}

Footprint Footprint::CreateCircularFootprint(const double radius,
                                             const double angular_resolution,
                                             const Vector2d& center) {
  // We have num_points * angular_resolution = 2 * pi (360 degrees).
  int num_points = std::round(2 * M_PI / angular_resolution);

  MatrixXd footprint_data(num_points, 2);

  VectorXd angles = VectorXd::LinSpaced(num_points, 0., M_PI);

  VectorXd x_coordinates = radius * Eigen::cos(angles.array()).matrix();
  VectorXd y_coordinates = radius * Eigen::sin(angles.array()).matrix();

  footprint_data.col(0) = x_coordinates;
  footprint_data.col(1) = y_coordinates;

  return OffsetFootprint(Footprint(footprint_data), center);
}

Footprint Footprint::CreateCircularFootprint(const double radius,
                                             const double angular_resolution,
                                             const Coordinate& center) {
  return CreateCircularFootprint(radius, angular_resolution, center.get_data());
}

//Footprint Footprint::CreateRoundedRectangularFootprint(
//    const double size_x, const double size_y, const double radius,
//    const double angular_resolution, const Vector2d& center) {
//  // We have num_points * angular_resolution = 2 * pi (360 degrees).
//  int num_points = std::round(2 * M_PI / angular_resolution);
//
//  MatrixXd footprint_data(4 * num_points, 2);
//
//
//}

}  // namespace blueprint
}  // namespace robot
}  // namespace morphac

