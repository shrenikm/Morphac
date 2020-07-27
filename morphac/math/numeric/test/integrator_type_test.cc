#include "gtest/gtest.h"

#include "math/numeric/include/integrator.h"

namespace {

using morphac::math::numeric::IntegratorType;

TEST(IntegratorTypeTest, Equality) {
  IntegratorType euler_type{IntegratorType::kEulerIntegrator};
  IntegratorType mid_point_type{IntegratorType::kMidPointIntegrator};
  IntegratorType rk4_type{IntegratorType::kRK4Integrator};

  ASSERT_TRUE(euler_type == IntegratorType::kEulerIntegrator);
  ASSERT_TRUE(mid_point_type == IntegratorType::kMidPointIntegrator);
  ASSERT_TRUE(rk4_type == IntegratorType::kRK4Integrator);

  ASSERT_TRUE(euler_type != IntegratorType::kMidPointIntegrator);
  ASSERT_TRUE(mid_point_type != IntegratorType::kRK4Integrator);
  ASSERT_TRUE(rk4_type != IntegratorType::kEulerIntegrator);
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

