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
  map_ = MatrixXd::Zero(height_, width_);
}

Environment2D::Environment2D(MatrixXd map, const double resolution)
    : width_(map.cols() * resolution),
      height_(map.rows() * resolution),
      resolution_(resolution) {
  MORPH_REQUIRE(map.cols() > 0, std::invalid_argument,
                "Non-positive map width.");
  MORPH_REQUIRE(map.rows() > 0, std::invalid_argument,
                "Non-positive map height.");
  MORPH_REQUIRE(resolution_ > 0, std::invalid_argument,
                "Non-positive environment resolution.");
  map_ = map;
}

const double Environment2D::get_width() { return width_; }

const double Environment2D::get_height() { return height_; }

const double Environment2D::get_resolution() { return resolution_; }

const MatrixXd& Environment2D::get_map() { return map_; }

void Environment2D::set_map(MatrixXd map) {
  // The map needs to have the same dimensions
  MORPH_REQUIRE((map.cols() * resolution_) == width_, std::invalid_argument,
                "Map width does not match.");
  MORPH_REQUIRE((map.rows() * resolution_) == height_, std::invalid_argument,
                "Map height does not match.");
  map_ = map;
}

}  // namespace environments
}  // namespace morphac

