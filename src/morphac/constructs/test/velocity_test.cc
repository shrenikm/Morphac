#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "constructs/include/velocity.h"

namespace {

using Eigen::VectorXd;

using morphac::constructs::Velocity;

class VelocityTest : public ::testing::Test {
 protected:
  VelocityTest() {}

  void SetUp() override {}

  Velocity velocity1_{Velocity(3)};
  Velocity velocity2_{Velocity(VectorXd::Zero(3))};
  VectorXd rand_velocity_ = VectorXd::Random(6);
  Velocity velocity3_{Velocity(rand_velocity_)};
  Velocity velocity4_ = velocity3_;
};

TEST_F(VelocityTest, Sizes) {
  ASSERT_EQ(velocity1_.get_size(), velocity2_.get_size());
  ASSERT_EQ(velocity1_.get_velocity_vector(), velocity2_.get_velocity_vector());
}

TEST_F(VelocityTest, CopyConstructor) {
  ASSERT_EQ(velocity3_.get_size(), velocity4_.get_size());
  for (int i = 0; i < velocity3_.get_size(); ++i) {
    ASSERT_EQ(velocity3_.get_velocity_at(i), velocity4_.get_velocity_at(i));
  }
}

TEST_F(VelocityTest, SetVelocity) {
  velocity3_.set_velocity_at(1, 7.0);
  ASSERT_EQ(velocity3_.get_velocity_at(1), 7.0);
}

TEST_F(VelocityTest, InvalidConstruction) {
  ASSERT_THROW(Velocity(0), std::invalid_argument);
  ASSERT_THROW(Velocity(VectorXd::Random(0)), std::invalid_argument);
}

TEST_F(VelocityTest, InvalidGet) {
  ASSERT_THROW(velocity1_.get_velocity_at(-1), std::out_of_range);
  ASSERT_THROW(velocity1_.get_velocity_at(3), std::out_of_range);
}

TEST_F(VelocityTest, InvalidSet) {
  ASSERT_THROW(velocity1_.set_velocity_vector(VectorXd::Random(4)),
               std::invalid_argument);
  ASSERT_THROW(velocity1_.set_velocity_vector(VectorXd::Random(2)),
               std::invalid_argument);
  ASSERT_THROW(velocity1_.set_velocity_at(-1, 1), std::out_of_range);
  ASSERT_THROW(velocity1_.set_velocity_at(7, 1), std::out_of_range);
}

TEST_F(VelocityTest, Addition) {
  VectorXd v1(3), v2(3), q1(3), q2(3);
  v1 << 1, 2, 3;
  v2 << 4, 5, 6;
  q1 << 5, 7, 9;
  q2 << 9, 12, 15;

  Velocity velocity1(v1);
  Velocity velocity2(v2);
  velocity1 += velocity2;
  ASSERT_TRUE(velocity1.get_velocity_vector().isApprox(q1));

  Velocity velocity3 = velocity1 + velocity2;
  ASSERT_TRUE(velocity3.get_velocity_vector().isApprox(q2));

  Velocity velocity4 = velocity2 + velocity1;
  ASSERT_TRUE(velocity3.get_velocity_vector().isApprox(
      velocity4.get_velocity_vector()));
}

TEST_F(VelocityTest, Subtraction) {
  VectorXd v1(3), v2(3), q1(3), q2(3);
  v1 << 1, 2, 3;
  v2 << 4, 5, 6;
  q1 << -3, -3, -3;
  q2 << -7, -8, -9;

  Velocity velocity1(v1);
  Velocity velocity2(v2);
  velocity1 -= velocity2;
  ASSERT_TRUE(velocity1.get_velocity_vector().isApprox(q1));

  Velocity velocity3 = velocity1 - velocity2;
  ASSERT_TRUE(velocity3.get_velocity_vector().isApprox(q2));

  Velocity velocity4 = velocity2 - velocity1;
  ASSERT_TRUE(velocity3.get_velocity_vector().isApprox(
      -1 * velocity4.get_velocity_vector()));
}

TEST_F(VelocityTest, Multiplication) {
  VectorXd v1(3), v2(3), q1(3), q2(3);
  v1 << 1, 2, 3;
  v2 << 4, 5, 6;
  q1 << 2, 4, 6;
  q2 << -4, -5, -6;

  Velocity velocity1(v1);
  Velocity velocity2(v2);

  velocity1 *= 2.0;
  ASSERT_TRUE(velocity1.get_velocity_vector().isApprox(q1));

  Velocity velocity3 = velocity2 * -1.0;
  Velocity velocity4 = -1 * velocity2;
  ASSERT_TRUE(velocity3.get_velocity_vector().isApprox(q2));
  ASSERT_TRUE(velocity4.get_velocity_vector().isApprox(q2));
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
