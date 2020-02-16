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

TEST_F(ControlInputTest, EmptyConstruction) {
  ControlInput input;

  // Accessors are invalid for empty velocity
  ASSERT_THROW(input.get_input_vector(), std::logic_error);
  ASSERT_THROW(input.get_input_at(0), std::logic_error);
  ASSERT_THROW(input.set_input_vector(VectorXd::Random(0)), std::logic_error);
  ASSERT_THROW(input.set_input_at(0, 0.0), std::logic_error);
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

TEST_F(ControlInputTest, Addition) {
  VectorXd i1(3), i2(3), d1(3), d2(3);
  i1 << 1, 2, 3;
  i2 << 4, 5, 6;
  d1 << 5, 7, 9;
  d2 << 9, 12, 15;

  ControlInput input1(i1);
  ControlInput input2(i2);
  input1 += input2;
  ASSERT_TRUE(input1.get_input_vector().isApprox(d1));

  ControlInput input3 = input1 + input2;
  ASSERT_TRUE(input3.get_input_vector().isApprox(d2));

  ControlInput input4 = input2 + input1;
  ASSERT_TRUE(input3.get_input_vector().isApprox(input4.get_input_vector()));
}

TEST_F(ControlInputTest, Subtraction) {
  VectorXd i1(3), i2(3), d1(3), d2(3);
  i1 << 1, 2, 3;
  i2 << 4, 5, 6;
  d1 << -3, -3, -3;
  d2 << -7, -8, -9;

  ControlInput input1(i1);
  ControlInput input2(i2);
  input1 -= input2;
  ASSERT_TRUE(input1.get_input_vector().isApprox(d1));

  ControlInput input3 = input1 - input2;
  ASSERT_TRUE(input3.get_input_vector().isApprox(d2));

  ControlInput input4 = input2 - input1;
  ASSERT_TRUE(
      input3.get_input_vector().isApprox(-1 * input4.get_input_vector()));
}

TEST_F(ControlInputTest, Multiplication) {
  VectorXd i1(3), i2(3), d1(3), d2(3);
  i1 << 1, 2, 3;
  i2 << 4, 5, 6;
  d1 << 2, 4, 6;
  d2 << -4, -5, -6;

  ControlInput input1(i1);
  ControlInput input2(i2);

  input1 *= 2.0;
  ASSERT_TRUE(input1.get_input_vector().isApprox(d1));

  ControlInput input3 = input2 * -1.0;
  ControlInput input4 = -1 * input2;
  ASSERT_TRUE(input3.get_input_vector().isApprox(d2));
  ASSERT_TRUE(input4.get_input_vector().isApprox(d2));
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
