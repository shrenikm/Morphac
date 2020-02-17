#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "mechanics/models/include/dubin_model.h"

namespace {

using std::string;

using Eigen::VectorXd;

using morphac::mechanics::models::DubinModel;
using morphac::constructs::State;

class DubinModelTest : public ::testing::Test {
 protected:
  DubinModelTest() {}

  void SetUp() override {}
};

TEST_F(DubinModelTest, Sizes) {
  DubinModel dubin{"dubin_model", 1.5};

  ASSERT_EQ(dubin.name, "dubin_model");
  ASSERT_EQ(dubin.size_pose, 3);
  ASSERT_EQ(dubin.size_velocity, 0);
  ASSERT_EQ(dubin.size_input, 1);
  ASSERT_EQ(dubin.speed, 1.5);
}

TEST_F(DubinModelTest, DerivativeComputation) {
  DubinModel dubin{"dubin_model", 2.5};

  //State state1{
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
