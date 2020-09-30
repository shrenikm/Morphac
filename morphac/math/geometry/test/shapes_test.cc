#include "math/geometry/include/shapes.h"

#include "gtest/gtest.h"

namespace {

using Eigen::Vector2d;

using morphac::common::aliases::Point;
using morphac::math::geometry::ArcShape;
using morphac::math::geometry::CircleShape;
using morphac::math::geometry::RectangleShape;
using morphac::math::geometry::RoundedRectangleShape;
using morphac::math::geometry::TriangleShape;
using morphac::utils::IsEqual;

class ShapesTest : public ::testing::Test {
 protected:
  ShapesTest() {
    // Set random seed for Eigen.
    srand(7);
  }

  void SetUp() override {}

  // Standard shapes
  ArcShape arc_shape_{Point(-1., 2.), M_PI / 4, M_PI, 2.};
};

TEST_F(ShapesTest, ArcShape) {
  ASSERT_TRUE(arc_shape_.center.isApprox(Vector2d(-1, 2)));
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}