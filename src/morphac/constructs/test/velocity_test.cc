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
  ASSERT_EQ(velocity1_.get_velocity(), velocity2_.get_velocity());
}

TEST_F(VelocityTest, CopyConstructor) {
  ASSERT_EQ(velocity3_.get_size(), velocity4_.get_size());
  for (int i = 0; i < velocity3_.get_size(); ++i) {
    ASSERT_EQ(velocity3_.get_velocity(i), velocity4_.get_velocity(i));
  }
}

TEST_F(VelocityTest, SetVelocity) {
  velocity3_.set_velocity(1, 7.0);
  ASSERT_EQ(velocity3_.get_velocity(1), 7.0);
}

TEST_F(VelocityTest, InvalidConstruction) {
  ASSERT_THROW(Velocity(0), std::invalid_argument);
  ASSERT_THROW(Velocity(VectorXd::Random(0)), std::invalid_argument);
}

TEST_F(VelocityTest, InvalidGet) {
  ASSERT_THROW(velocity1_.get_velocity(-1), std::out_of_range);
  ASSERT_THROW(velocity1_.get_velocity(3), std::out_of_range);
}

TEST_F(VelocityTest, InvalidSet) {
  ASSERT_THROW(velocity1_.set_velocity(VectorXd::Random(4)),
               std::invalid_argument);
  ASSERT_THROW(velocity1_.set_velocity(VectorXd::Random(2)),
               std::invalid_argument);
  ASSERT_THROW(velocity1_.set_velocity(-1, 1), std::out_of_range);
  ASSERT_THROW(velocity1_.set_velocity(7, 1), std::out_of_range);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
