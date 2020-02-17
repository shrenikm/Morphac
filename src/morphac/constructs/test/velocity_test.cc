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
  ASSERT_EQ(velocity3_.get_size(), 6);
}

TEST_F(VelocityTest, CopyConstructor) {
  ASSERT_EQ(velocity3_.get_size(), velocity4_.get_size());
  ASSERT_TRUE(velocity3_.get_velocity_vector().isApprox(
      velocity4_.get_velocity_vector()));
}

TEST_F(VelocityTest, GetVelocity) {
  ASSERT_TRUE(velocity1_.get_velocity_vector().isApprox(VectorXd::Zero(3)));

  for (int i = 0; i < velocity2_.get_size(); ++i) {
    ASSERT_EQ(velocity2_(i), 0);
  }
}

TEST_F(VelocityTest, SetVelocity) {
  velocity1_.set_velocity_vector(VectorXd::Ones(3));
  ASSERT_TRUE(velocity1_.get_velocity_vector().isApprox(VectorXd::Ones(3)));

  VectorXd v = VectorXd::Random(velocity3_.get_size());
  for (int i = 0; i < velocity3_.get_size(); ++i) {
    velocity3_(i) = v(i);
  }
  ASSERT_TRUE(velocity3_.get_velocity_vector().isApprox(v));
}

TEST_F(VelocityTest, ConstVelocityGet) {
  const Velocity velocity{3};

  // For a const Velocity, the values can only be accessed but not set, as a
  // reference (lvalue) is not returned for this overload of the operator.
  ASSERT_EQ(velocity(0), 0);
}

TEST_F(VelocityTest, InvalidConstruction) {
  ASSERT_THROW(Velocity{-1}, std::invalid_argument);
}

TEST_F(VelocityTest, EmptyConstruction) {
  Velocity velocity;

  // Assert emptiness
  ASSERT_TRUE(velocity.is_empty());

  // Accessors are invalid for empty Velocity
  ASSERT_THROW(velocity.get_velocity_vector(), std::logic_error);
  ASSERT_THROW(velocity(0), std::logic_error);
  ASSERT_THROW(velocity.set_velocity_vector(VectorXd::Random(0)),
               std::logic_error);
}

TEST_F(VelocityTest, InvalidGet) {
  ASSERT_THROW(velocity1_(-1), std::out_of_range);
  ASSERT_THROW(velocity1_(3), std::out_of_range);
}

TEST_F(VelocityTest, InvalidSet) {
  ASSERT_THROW(velocity1_.set_velocity_vector(VectorXd::Random(4)),
               std::invalid_argument);
  ASSERT_THROW(velocity1_.set_velocity_vector(VectorXd::Random(2)),
               std::invalid_argument);
}

TEST_F(VelocityTest, Addition) {
  VectorXd v1(3), v2(3), d1(3), d2(3);
  v1 << 1, 2, 3;
  v2 << 4, 5, 6;
  d1 << 5, 7, 9;
  d2 << 9, 12, 15;

  Velocity velocity1{v1};
  Velocity velocity2{v2};
  velocity1 += velocity2;
  ASSERT_TRUE(velocity1.get_velocity_vector().isApprox(d1));

  Velocity velocity3 = velocity1 + velocity2;
  ASSERT_TRUE(velocity3.get_velocity_vector().isApprox(d2));

  Velocity velocity4 = velocity2 + velocity1;
  ASSERT_TRUE(velocity3.get_velocity_vector().isApprox(
      velocity4.get_velocity_vector()));
}

TEST_F(VelocityTest, Subtraction) {
  VectorXd v1(3), v2(3), d1(3), d2(3);
  v1 << 1, 2, 3;
  v2 << 4, 5, 6;
  d1 << -3, -3, -3;
  d2 << -7, -8, -9;

  Velocity velocity1{v1};
  Velocity velocity2{v2};
  velocity1 -= velocity2;
  ASSERT_TRUE(velocity1.get_velocity_vector().isApprox(d1));

  Velocity velocity3 = velocity1 - velocity2;
  ASSERT_TRUE(velocity3.get_velocity_vector().isApprox(d2));

  Velocity velocity4 = velocity2 - velocity1;
  ASSERT_TRUE(velocity3.get_velocity_vector().isApprox(
      -1 * velocity4.get_velocity_vector()));
}

TEST_F(VelocityTest, Multiplication) {
  VectorXd v1(3), v2(3), d1(3), d2(3);
  v1 << 1, 2, 3;
  v2 << 4, 5, 6;
  d1 << 2, 4, 6;
  d2 << -4, -5, -6;

  Velocity velocity1{v1};
  Velocity velocity2{v2};

  velocity1 *= 2.0;
  ASSERT_TRUE(velocity1.get_velocity_vector().isApprox(d1));

  Velocity velocity3 = velocity2 * -1.0;
  Velocity velocity4 = -1 * velocity2;
  ASSERT_TRUE(velocity3.get_velocity_vector().isApprox(d2));
  ASSERT_TRUE(velocity4.get_velocity_vector().isApprox(d2));
}

TEST_F(VelocityTest, EmptyVelocityOperations) {
  // Basic operations on empty velocities must result in empty velocities.
  Velocity velocity1, velocity2;

  Velocity velocity_add = velocity1 + velocity2;
  ASSERT_TRUE(velocity_add.is_empty());

  Velocity velocity_sub = velocity1 - velocity2;
  ASSERT_TRUE(velocity_sub.is_empty());

  Velocity velocity_mult = velocity1 * 7.0;
  ASSERT_TRUE(velocity_mult.is_empty());
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
