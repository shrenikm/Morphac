#include "utils/include/angle_utils.h"

#include "gtest/gtest.h"

namespace {

using morphac::utils::NormalizeAngle;
using morphac::utils::ToDegrees;
using morphac::utils::ToRadians;

double precision = 1e-6;

TEST(AngleUtilsTest, ToDegrees) {
  ASSERT_NEAR(ToDegrees(0), 0, precision);
  ASSERT_NEAR(ToDegrees(M_PI / 2), 90, precision);
  ASSERT_NEAR(ToDegrees(M_PI), 180, precision);
  ASSERT_NEAR(ToDegrees(3 * M_PI / 2), 270, precision);
  ASSERT_NEAR(ToDegrees(2 * M_PI), 360, precision);

  // Negative angles.
  ASSERT_NEAR(ToDegrees(-M_PI / 2), -90, precision);
  ASSERT_NEAR(ToDegrees(-M_PI), -180, precision);
  ASSERT_NEAR(ToDegrees(-3 * M_PI / 2), -270, precision);
  ASSERT_NEAR(ToDegrees(-2 * M_PI), -360, precision);
}

TEST(AngleUtilsTest, ToRadians) {
  ASSERT_NEAR(ToRadians(0), 0., precision);
  ASSERT_NEAR(ToRadians(90), M_PI / 2, precision);
  ASSERT_NEAR(ToRadians(180), M_PI, precision);
  ASSERT_NEAR(ToRadians(270), 3 * M_PI / 2, precision);
  ASSERT_NEAR(ToRadians(360), 2 * M_PI, precision);

  // Negative angles.
  ASSERT_NEAR(ToRadians(-90), -M_PI / 2, precision);
  ASSERT_NEAR(ToRadians(-180), -M_PI, precision);
  ASSERT_NEAR(ToRadians(-270), -3 * M_PI / 2, precision);
  ASSERT_NEAR(ToRadians(-360), -2 * M_PI, precision);
}

TEST(AngleUtilsTest, NormalizeAngle) {
  // Test that already normalized angles remain unchanged.
  ASSERT_NEAR(NormalizeAngle(0), 0, precision);
  ASSERT_NEAR(NormalizeAngle(M_PI / 2), M_PI / 2, precision);
  ASSERT_NEAR(NormalizeAngle(M_PI), M_PI, precision);
  ASSERT_NEAR(NormalizeAngle(-M_PI / 2), -M_PI / 2, precision);

  // Normalization of 2 * pi
  ASSERT_NEAR(NormalizeAngle(2 * M_PI), 0, precision);

  // -pi should normalize to pi.
  ASSERT_NEAR(NormalizeAngle(-M_PI), M_PI, precision);

  // Angles that are positive in the last two quadrants.
  ASSERT_NEAR(NormalizeAngle(4 * M_PI / 3), -2 * M_PI / 3, precision);
  ASSERT_NEAR(NormalizeAngle(3 * M_PI / 2), -M_PI / 2, precision);
  ASSERT_NEAR(NormalizeAngle(5 * M_PI / 3), -M_PI / 3, precision);

  // Angles that are negative in the first two quadrants.
  ASSERT_NEAR(NormalizeAngle(-4 * M_PI / 3), 2 * M_PI / 3, precision);
  ASSERT_NEAR(NormalizeAngle(-3 * M_PI / 2), M_PI / 2, precision);
  ASSERT_NEAR(NormalizeAngle(-5 * M_PI / 3), M_PI / 3, precision);

  // Angles that are > 2 * pi but lie in the first two quadrants.
  ASSERT_NEAR(NormalizeAngle(2 * M_PI + M_PI / 3), M_PI / 3, precision);
  ASSERT_NEAR(NormalizeAngle(2 * M_PI + M_PI / 2), M_PI / 2, precision);
  ASSERT_NEAR(NormalizeAngle(2 * M_PI + 2 * M_PI / 3), 2 * M_PI / 3, precision);
  ASSERT_NEAR(NormalizeAngle(14 * M_PI + M_PI / 2), M_PI / 2, precision);

  // Angles that are < - 2 * pi but lie in the last two quadrants.
  ASSERT_NEAR(NormalizeAngle(-2 * M_PI - M_PI / 3), -M_PI / 3, precision);
  ASSERT_NEAR(NormalizeAngle(-2 * M_PI - M_PI / 2), -M_PI / 2, precision);
  ASSERT_NEAR(NormalizeAngle(-2 * M_PI - 2 * M_PI / 3), -2 * M_PI / 3,
              precision);
  ASSERT_NEAR(NormalizeAngle(-14 * M_PI - M_PI / 2), -M_PI / 2, precision);

  // Angles that are > 2 * pi but lie in the last two quadrants.
  ASSERT_NEAR(NormalizeAngle(2 * M_PI + 4 * M_PI / 3), -2 * M_PI / 3,
              precision);
  ASSERT_NEAR(NormalizeAngle(2 * M_PI + 3 * M_PI / 2), -M_PI / 2, precision);
  ASSERT_NEAR(NormalizeAngle(2 * M_PI + 5 * M_PI / 3), -M_PI / 3, precision);
  ASSERT_NEAR(NormalizeAngle(14 * M_PI + 3 * M_PI / 2), -M_PI / 2, precision);

  // Angles that are < - 2 * pi but  lie in the first two quadrants.
  ASSERT_NEAR(NormalizeAngle(-2 * M_PI - 4 * M_PI / 3), 2 * M_PI / 3,
              precision);
  ASSERT_NEAR(NormalizeAngle(-2 * M_PI - 3 * M_PI / 2), M_PI / 2, precision);
  ASSERT_NEAR(NormalizeAngle(-2 * M_PI - 5 * M_PI / 3), M_PI / 3, precision);
  ASSERT_NEAR(NormalizeAngle(-14 * M_PI - 3 * M_PI / 2), M_PI / 2, precision);
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
