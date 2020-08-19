#include "gtest/gtest.h"

#include "utils/include/numeric_utils.h"

namespace {

using morphac::utils::IsEqual;

TEST(NumericUtilsTest, IsEqual) {
  // Equality checks with default tolerances.

  // Regular float comparison.
  ASSERT_TRUE(IsEqual(0.1 + 0.1, 0.3 - 0.1));
  ASSERT_TRUE(IsEqual(8. / 3., 64. / 24.));
  ASSERT_FALSE(IsEqual(0.1, 0.1 + 1e-9));

  // Comparison of really small values.
  ASSERT_TRUE(IsEqual(0.3e-15 + 0.2e-15, 0.45e-15 + 0.05e-15));
  ASSERT_TRUE(IsEqual(8. / 1e16, 64. / 8e16));
  ASSERT_FALSE(IsEqual(1e-16, 1e-15));

  // Comparison of really large values.
  ASSERT_TRUE(IsEqual(3e15 + 4e15, 14e15 - 7e15));
  ASSERT_TRUE(IsEqual(8. / 1e-16, 64. / 8e-16));
  ASSERT_FALSE(IsEqual(7e15, 7.001e15));

  // Equality checks with custom tolerances.
  ASSERT_TRUE(IsEqual(0.1, 0.1001, 1e-3));
  ASSERT_TRUE(IsEqual(0.1, 0.2, 1., 1e-10));
  ASSERT_TRUE(IsEqual(0.1, 0.2, 1e-10, 1));
  ASSERT_FALSE(IsEqual(0.1, 0.2, 1e-2));
  ASSERT_FALSE(IsEqual(0.1, 0.2, 1e-10, 1e-2));
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
