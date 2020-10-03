#include "environment/include/map.h"

namespace morphac {
namespace environment {

using Eigen::MatrixXd;

using morphac::environment::Map;

Map::Map(const double width, const double height, const double resolution)
    : width_(width), height_(height), resolution_(resolution) {
  MORPH_REQUIRE(width_ > 0, std::invalid_argument, "Non-positive map width.");
  MORPH_REQUIRE(height_ > 0, std::invalid_argument, "Non-positive map height.");
  MORPH_REQUIRE(resolution_ > 0, std::invalid_argument,
                "Non-positive map resolution.");

  // The resolution is the real world size of one pixel. Once it is converted to
  // the image space, upon converting back, it should result in the same value.
  // If it does not, the resolution is invalid.

  // If this is not satisfied, we cannot guarantee the accurate image
  // representation of the map (Especially when obstacles are involved).
  int rows = height_ / resolution_;
  int cols = width_ / resolution_;

  MORPH_REQUIRE(std::fabs(width - cols * resolution_) <
                    std::numeric_limits<double>::epsilon(),
                std::invalid_argument, "Invalid resolution.");
  MORPH_REQUIRE(std::fabs(height - rows * resolution_) <
                    std::numeric_limits<double>::epsilon(),
                std::invalid_argument, "Invalid resolution.");

  data_ = MatrixXd::Zero(rows, cols);
}

Map::Map(const MatrixXd& data, const double resolution)
    : width_(data.cols() * resolution),
      height_(data.rows() * resolution),
      resolution_(resolution) {
  MORPH_REQUIRE(data.cols() > 0, std::invalid_argument,
                "Non-positive data width.");
  MORPH_REQUIRE(data.rows() > 0, std::invalid_argument,
                "Non-positive data height.");
  MORPH_REQUIRE(resolution_ > 0, std::invalid_argument,
                "Non-positive map resolution.");

  // The resolution is the real world size of one pixel. Once it is converted to
  // the image space, upon converting back, it should result in the same value.
  // If it does not, the resolution is invalid.

  // While creating the map with data, the resolution is always right
  // as the width and height are computed from the data and resolution and the
  // data is always valid dimension wise. The check below is just a failsafe.

  double width = data.cols() * resolution_;
  double height = data.rows() * resolution_;

  MORPH_REQUIRE(data.cols() == int(width / resolution_), std::invalid_argument,
                "Invalid resolution.");
  MORPH_REQUIRE(data.rows() == int(height / resolution_), std::invalid_argument,
                "Invalid resolution.");
  data_ = data;
}

double Map::get_width() const { return width_; }

double Map::get_height() const { return height_; }

double Map::get_resolution() const { return resolution_; }

const MatrixXd& Map::get_data() const { return data_; }

MatrixXd& Map::get_data_ref() { return data_; }

void Map::set_data(const MatrixXd& data) {
  // The data needs to have the same dimensions
  MORPH_REQUIRE((data.rows() * this->resolution_) == this->height_,
                std::invalid_argument, "Data height does not match.");
  MORPH_REQUIRE((data.cols() * this->resolution_) == this->width_,
                std::invalid_argument, "Data width does not match.");
  data_ = data;
}

Map Map::Evolve(const MatrixXd& data) {
  MORPH_REQUIRE(this->data_.rows() == data.rows(), std::invalid_argument,
                "Data height does not match.")
  MORPH_REQUIRE(this->data_.cols() == data.cols(), std::invalid_argument,
                "Data width does not match.")
  return Map(data, this->resolution_);
}

}  // namespace environment
}  // namespace morphac
