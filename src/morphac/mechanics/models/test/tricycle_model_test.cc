#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "mechanics/models/include/tricycle_model.h"

namespace {

using std::string;

using Eigen::VectorXd;

using morphac::constructs::ControlInput;
using morphac::constructs::State;
using morphac::mechanics::models::TricycleModel;

class TricycleModelTest : public ::testing::Test {
 protected:
  TricycleModelTest() {}

  void SetUp() override {}
};

TEST_F(TricycleModelTest, Construction) {
  TricycleModel tricycle_model{"tricycle_model", 1.5, 2.3};

  ASSERT_EQ(tricycle_model.name, "tricycle_model");
  ASSERT_EQ(tricycle_model.size_pose, 4);
  ASSERT_EQ(tricycle_model.size_velocity, 0);
  ASSERT_EQ(tricycle_model.size_input, 2);
  ASSERT_EQ(tricycle_model.radius, 1.5);
  ASSERT_EQ(tricycle_model.length, 2.3);
}

TEST_F(TricycleModelTest, InvalidConstruction) {
  ASSERT_THROW(TricycleModel("invalid", -1, 1), std::invalid_argument);
  ASSERT_THROW(TricycleModel("invalid", 0, 1), std::invalid_argument);
  ASSERT_THROW(TricycleModel("invalid", 1, -1), std::invalid_argument);
  ASSERT_THROW(TricycleModel("invalid", 1, -1), std::invalid_argument);
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

