#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "robot/blueprint/include/footprint.h"

namespace {

using Eigen::MatrixXd;

using morphac::robot::blueprint::Footprint;

class FootprintTest : public ::testing::Test {
 protected:
  FootprintTest() {
    // Set random seed for Eigen.
    srand(7);
    data_ = MatrixXd::Random(10, 2);
  }

  void SetUp() override {}

  MatrixXd data_;
};

TEST_F(FootprintTest, Construction) { Footprint footprint(data_); }

TEST_F(FootprintTest, CopyConstructor) {
  Footprint footprint1(data_);

  Footprint footprint2(footprint1);

  ASSERT_TRUE(footprint1.get_data().isApprox(footprint2.get_data()));
}

TEST_F(FootprintTest, CopyAssignment) {
  Footprint footprint1(data_);

  Footprint footprint2 = footprint1;

  ASSERT_TRUE(footprint1.get_data().isApprox(footprint2.get_data()));
}

TEST_F(FootprintTest, Accessors) {
  Footprint footprint(data_);
  ASSERT_TRUE(footprint.get_data().isApprox(data_));
}

TEST_F(FootprintTest, InvalidConstruction) {
  ASSERT_THROW(Footprint(MatrixXd::Zero(0, 0)), std::invalid_argument);
  ASSERT_THROW(Footprint(MatrixXd::Zero(0, 2)), std::invalid_argument);
  ASSERT_THROW(Footprint(MatrixXd::Zero(4, 3)), std::invalid_argument);
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
