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
  ASSERT_EQ(input3_.get_size(), 6);
}

TEST_F(ControlInputTest, CopyConstructor) {
  ASSERT_EQ(input3_.get_size(), input4_.get_size());
  ASSERT_TRUE(input3_.get_input_vector().isApprox(input4_.get_input_vector()));
}

TEST_F(ControlInputTest, GetInput) {
  ASSERT_TRUE(input1_.get_input_vector().isApprox(VectorXd::Zero(3)));

  for (int i = 0; i < input2_.get_size(); ++i) {
    ASSERT_EQ(input2_(i), 0);
  }
}

TEST_F(ControlInputTest, SetInput) {
  input1_.set_input_vector(VectorXd::Ones(3));
  ASSERT_TRUE(input1_.get_input_vector().isApprox(VectorXd::Ones(3)));

  VectorXd v = VectorXd::Random(input3_.get_size());
  for (int i = 0; i < input3_.get_size(); ++i) {
    input3_(i) = v(i);
  }
  ASSERT_TRUE(input3_.get_input_vector().isApprox(v));
}

TEST_F(ControlInputTest, InvalidConstruction) {
  ASSERT_THROW(ControlInput{-1}, std::invalid_argument);
}

TEST_F(ControlInputTest, EmptyConstruction) {
  ControlInput input;

  // Assert emptiness
  ASSERT_TRUE(input.is_empty());

  // Accessors are invalid for empty ControlInput
  ASSERT_THROW(input.get_input_vector(), std::logic_error);
  ASSERT_THROW(input(0), std::logic_error);
  ASSERT_THROW(input.set_input_vector(VectorXd::Random(0)), std::logic_error);
}

TEST_F(ControlInputTest, InvalidGet) {
  ASSERT_THROW(input1_(-1), std::out_of_range);
  ASSERT_THROW(input1_(3), std::out_of_range);
}

TEST_F(ControlInputTest, InvalidSet) {
  ASSERT_THROW(input1_.set_input_vector(VectorXd::Random(4)),
               std::invalid_argument);
  ASSERT_THROW(input1_.set_input_vector(VectorXd::Random(2)),
               std::invalid_argument);
}

TEST_F(ControlInputTest, Addition) {
  VectorXd i1(3), i2(3), d1(3), d2(3);
  i1 << 1, 2, 3;
  i2 << 4, 5, 6;
  d1 << 5, 7, 9;
  d2 << 9, 12, 15;

  ControlInput input1{i1};
  ControlInput input2{i2};
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

  ControlInput input1{i1};
  ControlInput input2{i2};
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

  ControlInput input1{i1};
  ControlInput input2{i2};

  input1 *= 2.0;
  ASSERT_TRUE(input1.get_input_vector().isApprox(d1));

  ControlInput input3 = input2 * -1.0;
  ControlInput input4 = -1 * input2;
  ASSERT_TRUE(input3.get_input_vector().isApprox(d2));
  ASSERT_TRUE(input4.get_input_vector().isApprox(d2));
}

TEST_F(ControlInputTest, EmptyControlInputOperations) {
  // Basic operations on empty velocities must result in empty velocities.
  ControlInput input1, input2;

  ControlInput input_add = input1 + input2;
  ASSERT_TRUE(input_add.is_empty());

  ControlInput input_sub = input1 - input2;
  ASSERT_TRUE(input_sub.is_empty());

  ControlInput input_mult = input1 * 7.0;
  ASSERT_TRUE(input_mult.is_empty());
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
