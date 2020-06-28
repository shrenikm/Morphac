#include "environments/include/environment.h"

namespace morphac {
namespace environments {

using Eigen::MatrixXd;

Environment::Environment(const double width, const double height,
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

  data_ = MatrixXd::Zero(rows, cols);
}

Environment::Environment(const MatrixXd& data, const double resolution)
    : width_(data.cols() * resolution),
      height_(data.rows() * resolution),
      resolution_(resolution) {
  MORPH_REQUIRE(data.cols() > 0, std::invalid_argument,
                "Non-positive data width.");
  MORPH_REQUIRE(data.rows() > 0, std::invalid_argument,
                "Non-positive data height.");
  MORPH_REQUIRE(resolution_ > 0, std::invalid_argument,
                "Non-positive environment resolution.");

  // The resolution is the real world size of one pixel. Once it is converted to
  // the image space, upon converting back, it should result in the same value.
  // If it does not, the resolution is invalid.

  // While creating the environment with data, the resolution is always right
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

double Environment::get_width() const { return width_; }

double Environment::get_height() const { return height_; }

double Environment::get_resolution() const { return resolution_; }

const MatrixXd& Environment::get_data() const { return data_; }

void Environment::set_data(const MatrixXd& data) {
  // The data needs to have the same dimensions
  MORPH_REQUIRE((data.cols() * resolution_) == width_, std::invalid_argument,
                "Data width does not match.");
  MORPH_REQUIRE((data.rows() * resolution_) == height_, std::invalid_argument,
                "Data height does not match.");
  data_ = data;
}

}  // namespace environments
}  // namespace morphac

