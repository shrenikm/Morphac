#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "constructs/include/input.h"

namespace {

using std::ostringstream;
using std::srand;

using Eigen::VectorXd;

using morphac::constructs::Input;

class InputTest : public ::testing::Test {
 protected:
  InputTest() {}

  void SetUp() override {
    // Set random seed for Eigen.
    srand(7);
  }

  Input input1_{Input(3)};
  Input input2_{Input(VectorXd::Zero(3))};
  VectorXd rand_input_ = VectorXd::Random(6);
  // Copy construction.
  Input input3_{Input(rand_input_)};
  Input input4_ = input3_;
};

TEST_F(InputTest, Sizes) {
  ASSERT_EQ(input1_.get_size(), input2_.get_size());
  ASSERT_EQ(input1_.get_input_vector(), input2_.get_input_vector());
  ASSERT_EQ(input3_.get_size(), 6);
}

TEST_F(InputTest, CopyConstructor) {
  ASSERT_EQ(input3_.get_size(), input4_.get_size());
  ASSERT_TRUE(input3_.get_input_vector().isApprox(input4_.get_input_vector()));
}

TEST_F(InputTest, GetInput) {
  ASSERT_TRUE(input1_.get_input_vector().isApprox(VectorXd::Zero(3)));

  for (int i = 0; i < input2_.get_size(); ++i) {
    ASSERT_EQ(input2_(i), 0);
  }
}

TEST_F(InputTest, SetInput) {
  input1_.set_input_vector(VectorXd::Ones(3));
  ASSERT_TRUE(input1_.get_input_vector().isApprox(VectorXd::Ones(3)));

  VectorXd v = VectorXd::Random(input3_.get_size());
  for (int i = 0; i < input3_.get_size(); ++i) {
    input3_(i) = v(i);
  }
  ASSERT_TRUE(input3_.get_input_vector().isApprox(v));
}

TEST_F(InputTest, ConstInput) {
  const Input input{3};

  // For a const Input, the values can only be accessed but not set, as a
  // reference (lvalue) is not returned for this overload of the operator.
  ASSERT_EQ(input(0), 0);
}

TEST_F(InputTest, InvalidConstruction) {
  ASSERT_THROW(Input{-1}, std::invalid_argument);
}

TEST_F(InputTest, EmptyConstruction) {
  Input input;

  // Assert emptiness
  ASSERT_TRUE(input.IsEmpty());

  // Accessors are invalid for empty Input
  ASSERT_THROW(input.get_input_vector(), std::logic_error);
  ASSERT_THROW(input(0), std::logic_error);
  ASSERT_THROW(input.set_input_vector(VectorXd::Random(0)), std::logic_error);
}

TEST_F(InputTest, InvalidGet) {
  ASSERT_THROW(input1_(-1), std::out_of_range);
  ASSERT_THROW(input1_(3), std::out_of_range);
}

TEST_F(InputTest, InvalidSet) {
  ASSERT_THROW(input1_.set_input_vector(VectorXd::Random(4)),
               std::invalid_argument);
  ASSERT_THROW(input1_.set_input_vector(VectorXd::Random(2)),
               std::invalid_argument);
}

TEST_F(InputTest, Addition) {
  VectorXd i1(3), i2(3), d1(3), d2(3);
  i1 << 1, 2, 3;
  i2 << 4, 5, 6;
  d1 << 5, 7, 9;
  d2 << 9, 12, 15;

  Input input1{i1};
  Input input2{i2};

  // Test trivial addition.
  input1 += Input::CreateLike(input1);
  ASSERT_TRUE(input1.get_input_vector().isApprox(i1));

  input1 = input1 + Input::CreateLike(input1);
  ASSERT_TRUE(input1.get_input_vector().isApprox(i1));

  input1 += input2;
  ASSERT_TRUE(input1.get_input_vector().isApprox(d1));

  Input input3 = input1 + input2;
  ASSERT_TRUE(input3.get_input_vector().isApprox(d2));

  Input input4 = input2 + input1;
  ASSERT_TRUE(input3.get_input_vector().isApprox(input4.get_input_vector()));
}

TEST_F(InputTest, Subtraction) {
  VectorXd i1(3), i2(3), d1(3), d2(3);
  i1 << 1, 2, 3;
  i2 << 4, 5, 6;
  d1 << -3, -3, -3;
  d2 << -7, -8, -9;

  Input input1{i1};
  Input input2{i2};

  // Test trivial subtraction.
  input1 -= Input::CreateLike(input1);
  ASSERT_TRUE(input1.get_input_vector().isApprox(i1));

  input1 = input1 - Input::CreateLike(input1);
  ASSERT_TRUE(input1.get_input_vector().isApprox(i1));

  input1 -= input2;
  ASSERT_TRUE(input1.get_input_vector().isApprox(d1));

  Input input3 = input1 - input2;
  ASSERT_TRUE(input3.get_input_vector().isApprox(d2));

  Input input4 = input2 - input1;
  ASSERT_TRUE(
      input3.get_input_vector().isApprox(-1 * input4.get_input_vector()));
}

TEST_F(InputTest, Multiplication) {
  VectorXd i1(3), i2(3), d1(3), d2(3);
  i1 << 1, 2, 3;
  i2 << 4, 5, 6;
  d1 << 2, 4, 6;
  d2 << -4, -5, -6;

  Input input1{i1};
  Input input2{i2};

  // Trivial multiplication.
  input1 = input1 * 1.0;
  ASSERT_TRUE(input1.get_input_vector().isApprox(i1));
  ASSERT_TRUE((0.0 * input1).get_input_vector().isApprox(VectorXd::Zero(3)));

  input1 *= 2.0;
  ASSERT_TRUE(input1.get_input_vector().isApprox(d1));

  Input input3 = input2 * -1.0;
  Input input4 = -1 * input2;
  ASSERT_TRUE(input3.get_input_vector().isApprox(d2));
  ASSERT_TRUE(input4.get_input_vector().isApprox(d2));
}

TEST_F(InputTest, StringRepresentation) {
  // Testing that the << operator is overloaded properly.
  // We don't test the actual string representation.
  ostringstream os;
  os << input1_;

  // Multiple pose object representations in the stream.
  os << " " << input3_ << std::endl;
}

TEST_F(InputTest, EmptyInputOperations) {
  // Basic operations on empty velocities must result in empty velocities.
  Input input1, input2;

  Input input_add = input1 + input2;
  ASSERT_TRUE(input_add.IsEmpty());

  Input input_sub = input1 - input2;
  ASSERT_TRUE(input_sub.IsEmpty());

  Input input_mult = input1 * 7.0;
  ASSERT_TRUE(input_mult.IsEmpty());
}

TEST_F(InputTest, CreateLike) {
  Input input1 = Input::CreateLike(input1_);
  Input input2 = Input::CreateLike(input3_);

  ASSERT_EQ(input1.get_size(), 3);
  ASSERT_TRUE(input1.get_input_vector().isApprox(VectorXd::Zero(3)));

  ASSERT_EQ(input2.get_size(), 6);
  ASSERT_TRUE(input2.get_input_vector().isApprox(VectorXd::Zero(6)));
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
