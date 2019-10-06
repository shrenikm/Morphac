#include "environments/include/environment2D.h"

namespace morphac {
namespace environments {

using Eigen::MatrixXd;

Environment2D::Environment2D(int width, int height)
    : width_(width), height_(height) {
  MORPH_REQUIRE(width_ > 0, std::invalid_argument,
                "Non-positive environment width.");
  MORPH_REQUIRE(height_ > 0, std::invalid_argument,
                "Non-positive environment height.");
  map_ = MatrixXd::Zero(height_, width_);
}

Environment2D::Environment2D(MatrixXd map)
    : width_(map.cols()), height_(map.rows()) {
  MORPH_REQUIRE(map.cols() > 0, std::invalid_argument,
                "Non-positive map width.");
  MORPH_REQUIRE(map.rows() > 0, std::invalid_argument,
                "Non-positive map height.");
  map_ = map;
}

int Environment2D::get_width() { return width_; }

int Environment2D::get_height() { return height_; }

MatrixXd Environment2D::get_map() { return map_; }

void Environment2D::set_map(MatrixXd map) {
  // The map needs to have the same dimensions
  MORPH_REQUIRE(map.cols() == width_, std::invalid_argument,
                "Map width does not match.");
  MORPH_REQUIRE(map.rows() == height_, std::invalid_argument,
                "Map height does not match.");
  map_ = map;
}

}  // namespace environments
}  // namespace morphac

