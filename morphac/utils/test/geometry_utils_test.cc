#include "gtest/gtest.h"

#include "utils/include/geometry_utils.h"

namespace {

using std::sqrt;

using Eigen::MatrixXd;
using Eigen::Vector2d;
using Eigen::VectorXd;

using morphac::utils::CreateArc;
using morphac::utils::CreateCircularPolygon;
using morphac::utils::CreateRectangularPolygon;
using morphac::utils::CreateRoundedRectangularPolygon;

TEST(GeometryUtilsTest, CreateRectangularPolygon) {
  // Rectangle without any transformation.
  double size_x = 6., size_y = 4.;
  Points rectangle =
      CreateRectangularPolygon(size_x, size_y, 0., Vector2d::Zero());

  // Make sure that it is a valid rectangle.
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

