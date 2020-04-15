#include "environments/include/environment2D.h"

namespace morphac {
namespace environments {

using Eigen::MatrixXd;

Environment2D::Environment2D(const double width, const double height,
                             const double resolution)
    : width_(width), height_(height), resolution_(resolution) {
  MORPH_REQUIRE(width_ > 0, std::invalid_argument,
                "Non-positive environment width.");
  MORPH_REQUIRE(height_ > 0, std::invalid_argument,
                "Non-positive environment height.");
  MORPH_REQUIRE(resolution_ > 0, std::invalid_argument,
                "Non-positive environment resolution.");

  // The resolution is the real world size of one pixel. Once it is converted to
  // the image space, upon converting back, it should result in the same value.
  // If it does not, the resolution is invalid.

  // If this is not satisfied, we cannot guarantee the accurate image
  // representation of the environment (Especially when obstacles are involved).
  int rows = height_ / resolution_;
  int cols = width_ / resolution_;

  MORPH_REQUIRE(std::fabs(width - cols * resolution_) <
                    std::numeric_limits<double>::epsilon(),
                std::invalid_argument, "Invalid resolution.");
  MORPH_REQUIRE(std::fabs(height - rows * resolution_) <
                    std::numeric_limits<double>::epsilon(),
                std::invalid_argument, "Invalid resolution.");

  map_ = MatrixXd::Zero(rows, cols);
}

Environment2D::Environment2D(const MatrixXd& map, const double resolution)
    : width_(map.cols() * resolution),
      height_(map.rows() * resolution),
      resolution_(resolution) {
  MORPH_REQUIRE(map.cols() > 0, std::invalid_argument,
                "Non-positive map width.");
  MORPH_REQUIRE(map.rows() > 0, std::invalid_argument,
                "Non-positive map height.");
  MORPH_REQUIRE(resolution_ > 0, std::invalid_argument,
                "Non-positive environment resolution.");

  // The resolution is the real world size of one pixel. Once it is converted to
  // the image space, upon converting back, it should result in the same value.
  // If it does not, the resolution is invalid.

  // While creating the environment with a map, the resolution is always right
  // as the width and height are computed from the map and resolution and the
  // map is always valid dimension wise. The check below is just a failsafe.

  double width = map.cols() * resolution_;
  double height = map.rows() * resolution_;

  MORPH_REQUIRE(map.cols() == int(width / resolution_), std::invalid_argument,
                "Invalid resolution.");
  MORPH_REQUIRE(map.rows() == int(height / resolution_), std::invalid_argument,
                "Invalid resolution.");
  map_ = map;
}

double Environment2D::get_width() const { return width_; }

double Environment2D::get_height() const { return height_; }

double Environment2D::get_resolution() const { return resolution_; }

const MatrixXd& Environment2D::get_map() const { return map_; }

void Environment2D::set_map(const MatrixXd& map) {
  // The map needs to have the same dimensions
  MORPH_REQUIRE((map.cols() * resolution_) == width_, std::invalid_argument,
                "Map width does not match.");
  MORPH_REQUIRE((map.rows() * resolution_) == height_, std::invalid_argument,
                "Map height does not match.");
  map_ = map;
}

}  // namespace environments
}  // namespace morphac

