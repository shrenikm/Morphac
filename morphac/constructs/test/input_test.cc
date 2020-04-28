#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "constructs/include/input.h"

namespace {

using std::initializer_list;
using std::make_unique;
using std::ostringstream;
using std::srand;
using std::unique_ptr;

using Eigen::VectorXd;

using morphac::constructs::Input;

class InputTest : public ::testing::Test {
 protected:
  InputTest() {
    input1_ = make_unique<Input>(3);
    input2_ = make_unique<Input>(VectorXd::Zero(4));
    input3_ = make_unique<Input>(initializer_list<double>{0, 0, 0, 0, 0});
  }

  void SetUp() override {
    // Set random seed for Eigen.
    srand(7);
  }

  unique_ptr<Input> input1_, input2_, input3_;
};

TEST_F(InputTest, CopyConstructor) {
  Input input1(*input1_);

  VectorXd input_vector = VectorXd::Random(4);
  Input input2(input_vector);
  Input input3(input2);

  ASSERT_TRUE(input1.get_input_vector().isApprox(VectorXd::Zero(3)));
  ASSERT_TRUE(input3.get_input_vector().isApprox(input_vector));
}

TEST_F(InputTest, InvalidConstruction) {
  ASSERT_THROW(Input(-1), std::invalid_argument);
}

TEST_F(InputTest, ConstInput) {
  // For a const Input, the values can only be accessed but not set, as a
  // reference (lvalue) is not returned for this overload of the operator.

  const Input input(3);

  ASSERT_EQ(input.get_size(), 3);
  ASSERT_TRUE(input.get_input_vector().isApprox(VectorXd::Zero(3)));

  // Making sure position accessing works.
  for (int i = 0; i < input.get_size(); ++i) {
    ASSERT_EQ(input(i), 0);
  }

  // After const casting, we should be able to modify the vector.
  const_cast<Input &>(input).set_input_vector(VectorXd::Ones(3));
  ASSERT_TRUE(input.get_input_vector().isApprox(VectorXd::Ones(3)));
}

TEST_F(InputTest, EmptyConstruction) {
  Input input(0);

  // Assert emptiness.
  ASSERT_TRUE(input.IsEmpty());
  ASSERT_TRUE(Input(VectorXd::Zero(0)).IsEmpty());
  ASSERT_TRUE(Input{}.IsEmpty());

  // Accessors are invalid for empty Input
  ASSERT_THROW(input.get_input_vector(), std::logic_error);
  ASSERT_THROW(input(0), std::logic_error);
  ASSERT_THROW(input.set_input_vector(VectorXd::Random(0)), std::logic_error);
}

TEST_F(InputTest, Sizes) {
  ASSERT_EQ(input1_->get_size(), 3);
  ASSERT_EQ(input2_->get_size(), 4);
  ASSERT_EQ(input3_->get_size(), 5);

  // Empty Input.
  ASSERT_EQ(Input(0).get_size(), 0);
}

TEST_F(InputTest, GetInputVector) {
  ASSERT_TRUE(input1_->get_input_vector().isApprox(VectorXd::Zero(3)));
  ASSERT_TRUE(input2_->get_input_vector().isApprox(VectorXd::Zero(4)));
  ASSERT_TRUE(input3_->get_input_vector().isApprox(VectorXd::Zero(5)));

  VectorXd input_vector = VectorXd::Random(6);
  Input input(input_vector);

  ASSERT_TRUE(input.get_input_vector().isApprox(input_vector));
}

TEST_F(InputTest, GetInputAt) {
  for (int i = 0; i < input1_->get_size(); ++i) {
    ASSERT_EQ((*input1_)(i), 0);
  }
  for (int i = 0; i < input2_->get_size(); ++i) {
    ASSERT_EQ((*input2_)(i), 0);
  }
  for (int i = 0; i < input3_->get_size(); ++i) {
    ASSERT_EQ((*input3_)(i), 0);
  }

  // Arbitrary Input.
  VectorXd input_vector = VectorXd::Random(7);
  Input input(input_vector);

  for (int i = 0; i < input.get_size(); ++i) {
    ASSERT_EQ(input(i), input_vector(i));
  }

  // Invalid get at.
  ASSERT_THROW((*input1_)(-1), std::out_of_range);
  ASSERT_THROW((*input1_)(3), std::out_of_range);

  ASSERT_THROW((*input2_)(-1), std::out_of_range);
  ASSERT_THROW((*input2_)(4), std::out_of_range);

  ASSERT_THROW((*input3_)(-1), std::out_of_range);
  ASSERT_THROW((*input3_)(5), std::out_of_range);
}

TEST_F(InputTest, SetInputVector) {
  VectorXd input_vector = VectorXd::Random(4);
  VectorXd expected_vector(5);
  expected_vector << 1, 0, -1, 2.5, 0;

  input1_->set_input_vector(VectorXd::Ones(3));
  input2_->set_input_vector(input_vector);
  input3_->set_input_vector({1, 0, -1, 2.5, 0});

  ASSERT_TRUE(input1_->get_input_vector().isApprox(VectorXd::Ones(3)));
  ASSERT_TRUE(input2_->get_input_vector().isApprox(input_vector));
  ASSERT_TRUE(input3_->get_input_vector().isApprox(expected_vector));

  // Invalid set vector.
  ASSERT_THROW(input1_->set_input_vector(VectorXd::Ones(2)),
               std::invalid_argument);
  ASSERT_THROW(input2_->set_input_vector(VectorXd::Ones(5)),
               std::invalid_argument);
  ASSERT_THROW(input3_->set_input_vector({}), std::invalid_argument);
  ASSERT_THROW(input3_->set_input_vector({1, 2, 3, 4}), std::invalid_argument);
  ASSERT_THROW(input3_->set_input_vector({1, 2, 1, 2, 1, 2}),
               std::invalid_argument);
}

TEST_F(InputTest, SetInputAt) {
  for (int i = 0; i < input1_->get_size(); ++i) {
    (*input1_)(i) = 1;
  }
  for (int i = 0; i < input2_->get_size(); ++i) {
    (*input2_)(i) = 2;
  }
  for (int i = 0; i < input3_->get_size(); ++i) {
    (*input3_)(i) = -3;
  }

  ASSERT_TRUE(input1_->get_input_vector().isApprox(VectorXd::Ones(3)));
  ASSERT_TRUE(input2_->get_input_vector().isApprox(2 * VectorXd::Ones(4)));
  ASSERT_TRUE(input3_->get_input_vector().isApprox(-3 * VectorXd::Ones(5)));

  // Invalid set at.
  ASSERT_THROW((*input1_)(-1) = 0, std::out_of_range);
  ASSERT_THROW((*input1_)(3) = 1, std::out_of_range);

  ASSERT_THROW((*input2_)(-1) = 0, std::out_of_range);
  ASSERT_THROW((*input2_)(4) = 1, std::out_of_range);

  ASSERT_THROW((*input3_)(-1) = 0, std::out_of_range);
  ASSERT_THROW((*input3_)(5) = 1, std::out_of_range);
}

TEST_F(InputTest, Addition) {
  VectorXd i1(3), i2(3), d1(3), d2(3);
  i1 << 1, 2, 3;
  i2 << 4, -5, 6;
  d1 << 5, -3, 9;
  d2 << 9, -8, 15;

  Input input1{1, 2, 3};
  Input input2(i2);

  // Trivial addition.
  input1 += Input::CreateLike(input1);
  ASSERT_TRUE(input1.get_input_vector().isApprox(i1));

  input1 = input1 + Input::CreateLike(input1);
  ASSERT_TRUE(input1.get_input_vector().isApprox(i1));

  input1 += input2;
  ASSERT_TRUE(input1.get_input_vector().isApprox(d1));

  // Commutativity.
  Input input3 = input1 + input2;
  ASSERT_TRUE(input3.get_input_vector().isApprox(d2));

  Input input4 = input2 + input1;
  ASSERT_TRUE(input3.get_input_vector().isApprox(input4.get_input_vector()));

  // Empty addition.
  Input empty_input1(0), empty_input2{};

  Input empty_input_add = empty_input1 + empty_input2;
  ASSERT_TRUE(empty_input_add.IsEmpty());
}

TEST_F(InputTest, Subtraction) {
  VectorXd i1(3), i2(3), d1(3), d2(3);
  i1 << 1, 2, 3;
  i2 << 4, -5, 6;
  d1 << -3, 7, -3;
  d2 << -7, 12, -9;

  Input input1({1, 2, 3});
  Input input2(i2);

  // Trivial subtraction.
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

  // Empty subtraction.
  Input empty_input1(0), empty_input2{};

  Input empty_input_sub = empty_input1 - empty_input2;
  ASSERT_TRUE(empty_input_sub.IsEmpty());
}

TEST_F(InputTest, Multiplication) {
  VectorXd i1(3), i2(3), d1(3), d2(3);
  i1 << 1, 2, 3;
  i2 << 4, -5, 6;
  d1 << 2, 4, 6;
  d2 << -6, 7.5, -9;

  Input input1({1, 2, 3});
  Input input2(i2);

  // Trivial multiplication.
  input1 = input1 * 1.0;
  ASSERT_TRUE(input1.get_input_vector().isApprox(i1));
  ASSERT_TRUE((0.0 * input1).get_input_vector().isApprox(VectorXd::Zero(3)));

  input1 *= 2.0;
  ASSERT_TRUE(input1.get_input_vector().isApprox(d1));

  // Commutativity.
  Input input3 = input2 * -1.5;
  Input input4 = -1.5 * input2;
  ASSERT_TRUE(input3.get_input_vector().isApprox(d2));
  ASSERT_TRUE(input4.get_input_vector().isApprox(d2));

  // Empty multiplication.
  Input empty_input1(0), empty_input2{};

  Input empty_input_mult1 = empty_input1 * 7.0;
  Input empty_input_mult2 = empty_input2 * 7.0;
  ASSERT_TRUE(empty_input_mult1.IsEmpty());
  ASSERT_TRUE(empty_input_mult2.IsEmpty());
}

TEST_F(InputTest, Equality) {
  ASSERT_TRUE(Input(3) == Input(3));
  ASSERT_TRUE(Input(3) == Input(VectorXd::Zero(3)));
  ASSERT_TRUE(Input(VectorXd::Ones(2)) == Input({1, 1}));
  ASSERT_TRUE(Input({1, 2}) == Input({1, 2}));

  ASSERT_TRUE(Input(3) != Input(2));
  ASSERT_TRUE(Input(3) != Input(VectorXd::Zero(2)));
  ASSERT_TRUE(Input(2) != Input({0}));
  ASSERT_TRUE(Input({1, 2}) != Input({3, 4}));
  ASSERT_TRUE(Input({1, 2}) != Input({1, 2.000001}));
}

TEST_F(InputTest, StringRepresentation) {
  // Testing that the << operator is overloaded properly.
  // We don't test the actual string representation.
  ostringstream os;
  os << (*input1_);

  // Multiple input object representations in the stream.
  os << " " << (*input2_) << std::endl;
}

TEST_F(InputTest, CreateLike) {
  Input input1 = Input::CreateLike(*input1_);
  Input input2 = Input::CreateLike(*input2_);
  Input input3 = Input::CreateLike(*input3_);

  ASSERT_EQ(input1.get_size(), 3);
  ASSERT_TRUE(input1.get_input_vector().isApprox(VectorXd::Zero(3)));

  ASSERT_EQ(input2.get_size(), 4);
  ASSERT_TRUE(input2.get_input_vector().isApprox(VectorXd::Zero(4)));

  ASSERT_EQ(input3.get_size(), 5);
  ASSERT_TRUE(input3.get_input_vector().isApprox(VectorXd::Zero(5)));
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
