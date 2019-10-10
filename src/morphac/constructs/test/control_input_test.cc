#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "constructs/include/control_input.h"

namespace {

using Eigen::VectorXd;

using morphac::constructs::ControlInput;

class ControlInputTest : public ::testing::Test {
 protected:
  ControlInputTest() {}

  void SetUp() override {}

  ControlInput input1_{ControlInput(3)};
  ControlInput input2_{ControlInput(VectorXd::Zero(3))};
  VectorXd rand_input_ = VectorXd::Random(6);
  ControlInput input3_{ControlInput(rand_input_)};
  ControlInput input4_ = input3_;
};

TEST_F(ControlInputTest, Sizes) {
  ASSERT_EQ(input1_.get_size(), input2_.get_size());
  ASSERT_EQ(input1_.get_input_vector(), input2_.get_input_vector());
}

TEST_F(ControlInputTest, CopyConstructor) {
  ASSERT_EQ(input3_.get_size(), input4_.get_size());
  for (int i = 0; i < input3_.get_size(); ++i) {
    ASSERT_EQ(input3_.get_input_at(i), input4_.get_input_at(i));
  }
}

TEST_F(ControlInputTest, SetControlInput) {
  input3_.set_input_at(1, 7.0);
  ASSERT_EQ(input3_.get_input_at(1), 7.0);
}

TEST_F(ControlInputTest, InvalidConstruction) {
  ASSERT_THROW(ControlInput(0), std::invalid_argument);
  ASSERT_THROW(ControlInput(VectorXd::Random(0)), std::invalid_argument);
}

TEST_F(ControlInputTest, InvalidGet) {
  ASSERT_THROW(input1_.get_input_at(-1), std::out_of_range);
  ASSERT_THROW(input1_.get_input_at(3), std::out_of_range);
}

TEST_F(ControlInputTest, InvalidSet) {
  ASSERT_THROW(input1_.set_input_vector(VectorXd::Random(4)),
               std::invalid_argument);
  ASSERT_THROW(input1_.set_input_vector(VectorXd::Random(2)),
               std::invalid_argument);
  ASSERT_THROW(input1_.set_input_at(-1, 1), std::out_of_range);
  ASSERT_THROW(input1_.set_input_at(7, 1), std::out_of_range);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
