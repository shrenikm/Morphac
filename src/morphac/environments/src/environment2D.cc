#include "environments/include/environment2D.h"

namespace morphac {
namespace environments {

using Eigen::MatrixXd;

Environment2D::Environment2D(int width, int height, int origin_x, int origin_y)
    : width_(width), height_(height), origin_x_(origin_x), origin_y_(origin_y) {
  MORPH_REQUIRE(width_ > 0, "Non-positive environment width.");
  MORPH_REQUIRE(height_ > 0, "Non-positive environment height.");
  MORPH_REQUIRE((origin_x_ >= 0 && origin_x_ < width_),
                "The origin's x coordinate is outside the map.")
  MORPH_REQUIRE((origin_y_ >= 0 && origin_y_ < height_),
                "The origin's y coordinate is outside the map.")
  map_ = MatrixXd::Zero(height_, width_);
}

Environment2D::Environment2D(MatrixXd map, int origin_x, int origin_y)
    : width_(map.cols()),
      height_(map.rows()),
      origin_x_(origin_x),
      origin_y_(origin_y) {
  MORPH_REQUIRE(map.cols() > 0, "Non-positive map width.");
  MORPH_REQUIRE(map.rows() > 0, "Non-positive map height.");
  MORPH_REQUIRE((origin_x_ >= 0 && origin_x_ < width_),
                "The origin's x coordinate is outside the map.")
  MORPH_REQUIRE((origin_y_ >= 0 && origin_y_ < height_),
                "The origin's y coordinate is outside the map.")
  map_ = map;
}

int Environment2D::get_width() {
  return width_;
}

int Environment2D::get_height() {
  return height_;
}

MatrixXd Environment2D::get_map() {
  return map_;
}

}  // namespace environments
}  // namespace morphac

