#include "gtest/gtest.h"

#include "utils/include/angle_utils.h"

namespace {

using morphac::utils::ToDegrees;
using morphac::utils::ToRadians;
using morphac::utils::NormalizeAngle;

class AngleUtilsTest : public ::testing::Test {
 protected:
  AngleUtilsTest() : precision_(1e-6) {
    // Set random seed for Eigen.
    srand(7);
  }

  void SetUp() override {}
  double precision_;
};

TEST_F(AngleUtilsTest, ToDegrees) {
  ASSERT_NEAR(ToDegrees(0), 0, precision_);
  ASSERT_NEAR(ToDegrees(M_PI / 2), 90, precision_);
  ASSERT_NEAR(ToDegrees(M_PI), 180, precision_);
  ASSERT_NEAR(ToDegrees(3 * M_PI / 2), 270, precision_);
  ASSERT_NEAR(ToDegrees(2 * M_PI), 360, precision_);

  // Negative angles.
  ASSERT_NEAR(ToDegrees(-M_PI / 2), -90, precision_);
  ASSERT_NEAR(ToDegrees(-M_PI), -180, precision_);
  ASSERT_NEAR(ToDegrees(-3 * M_PI / 2), -270, precision_);
  ASSERT_NEAR(ToDegrees(-2 * M_PI), -360, precision_);
}

TEST_F(AngleUtilsTest, ToRadians) {
  ASSERT_NEAR(ToRadians(0), 0., precision_);
  ASSERT_NEAR(ToRadians(90), M_PI / 2, precision_);
  ASSERT_NEAR(ToRadians(180), M_PI, precision_);
  ASSERT_NEAR(ToRadians(270), 3 * M_PI / 2, precision_);
  ASSERT_NEAR(ToRadians(360), 2 * M_PI, precision_);

  // Negative angles.
  ASSERT_NEAR(ToRadians(-90), -M_PI / 2, precision_);
  ASSERT_NEAR(ToRadians(-180), -M_PI, precision_);
  ASSERT_NEAR(ToRadians(-270), -3 * M_PI / 2, precision_);
  ASSERT_NEAR(ToRadians(-360), -2 * M_PI, precision_);
}

TEST_F(AngleUtilsTest, NormalizeAngle) {
  // Test that already normalized angles remain unchanged.
  ASSERT_NEAR(NormalizeAngle(0), 0, precision_);
  ASSERT_NEAR(NormalizeAngle(M_PI / 2), M_PI / 2, precision_);
  ASSERT_NEAR(NormalizeAngle(M_PI), M_PI, precision_);
  ASSERT_NEAR(NormalizeAngle(-M_PI / 2), -M_PI / 2, precision_);

  // Normalization of 2 * pi
  ASSERT_NEAR(NormalizeAngle(2 * M_PI), 0, precision_);

  // -pi should normalize to pi.
  ASSERT_NEAR(NormalizeAngle(-M_PI), M_PI, precision_);

  // Angles that are positive in the last two quadrants.
  ASSERT_NEAR(NormalizeAngle(4 * M_PI / 3), -2 * M_PI / 3, precision_);
  ASSERT_NEAR(NormalizeAngle(3 * M_PI / 2), -M_PI / 2, precision_);
  ASSERT_NEAR(NormalizeAngle(5 * M_PI / 3), -M_PI / 3, precision_);

  // Angles that are negative in the first two quadrants.
  ASSERT_NEAR(NormalizeAngle(-4 * M_PI / 3), 2 * M_PI / 3, precision_);
  ASSERT_NEAR(NormalizeAngle(-3 * M_PI / 2), M_PI / 2, precision_);
  ASSERT_NEAR(NormalizeAngle(-5 * M_PI / 3), M_PI / 3, precision_);

  // Angles that are > 2 * pi but lie in the first two quadrants.
  ASSERT_NEAR(NormalizeAngle(2 * M_PI + M_PI / 3), M_PI / 3, precision_);
  ASSERT_NEAR(NormalizeAngle(2 * M_PI + M_PI / 2), M_PI / 2, precision_);
  ASSERT_NEAR(NormalizeAngle(2 * M_PI + 2 * M_PI / 3), 2 * M_PI / 3,
              precision_);
  ASSERT_NEAR(NormalizeAngle(14 * M_PI + M_PI / 2), M_PI / 2, precision_);

  // Angles that are < - 2 * pi but lie in the last two quadrants.
  ASSERT_NEAR(NormalizeAngle(-2 * M_PI - M_PI / 3), -M_PI / 3, precision_);
  ASSERT_NEAR(NormalizeAngle(-2 * M_PI - M_PI / 2), -M_PI / 2, precision_);
  ASSERT_NEAR(NormalizeAngle(-2 * M_PI - 2 * M_PI / 3), -2 * M_PI / 3,
              precision_);
  ASSERT_NEAR(NormalizeAngle(-14 * M_PI - M_PI / 2), -M_PI / 2, precision_);

  // Angles that are > 2 * pi but lie in the last two quadrants.
  ASSERT_NEAR(NormalizeAngle(2 * M_PI + 4 * M_PI / 3), -2 * M_PI / 3,
              precision_);
  ASSERT_NEAR(NormalizeAngle(2 * M_PI + 3 * M_PI / 2), -M_PI / 2, precision_);
  ASSERT_NEAR(NormalizeAngle(2 * M_PI + 5 * M_PI / 3), -M_PI / 3, precision_);
  ASSERT_NEAR(NormalizeAngle(14 * M_PI + 3 * M_PI / 2), -M_PI / 2, precision_);

  // Angles that are < - 2 * pi but  lie in the first two quadrants.
  ASSERT_NEAR(NormalizeAngle(-2 * M_PI - 4 * M_PI / 3), 2 * M_PI / 3,
              precision_);
  ASSERT_NEAR(NormalizeAngle(-2 * M_PI - 3 * M_PI / 2), M_PI / 2, precision_);
  ASSERT_NEAR(NormalizeAngle(-2 * M_PI - 5 * M_PI / 3), M_PI / 3, precision_);
  ASSERT_NEAR(NormalizeAngle(-14 * M_PI - 3 * M_PI / 2), M_PI / 2, precision_);
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
