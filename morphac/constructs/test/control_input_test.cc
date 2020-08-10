#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "constructs/include/control_input.h"

namespace {

using std::initializer_list;
using std::make_unique;
using std::ostringstream;
using std::srand;
using std::unique_ptr;

using Eigen::VectorXd;

using morphac::constructs::ControlInput;

class ControlInputTest : public ::testing::Test {
 protected:
  ControlInputTest() {
    // Set random seed for Eigen.
    srand(7);
    control_input1_ = make_unique<ControlInput>(3);
    control_input2_ = make_unique<ControlInput>(VectorXd::Zero(4));
    control_input3_ =
        make_unique<ControlInput>(initializer_list<double>{0, 0, 0, 0, 0});
  }

  void SetUp() override {}

  unique_ptr<ControlInput> control_input1_, control_input2_, control_input3_;
};

TEST_F(ControlInputTest, CopyConstructor) {
  ControlInput control_input1(*control_input1_);

  VectorXd data = VectorXd::Random(4);
  ControlInput control_input2(data);
  ControlInput control_input3(control_input2);

  ASSERT_TRUE(control_input1.get_data().isApprox(VectorXd::Zero(3)));
  ASSERT_TRUE(control_input3.get_data().isApprox(data));
}

TEST_F(ControlInputTest, CopyAssignment) {
  ControlInput control_input1 = *control_input1_;

  VectorXd data = VectorXd::Random(4);
  ControlInput control_input2(data);
  ControlInput control_input3 = control_input2;

  ASSERT_TRUE(control_input1.get_data().isApprox(VectorXd::Zero(3)));
  ASSERT_TRUE(control_input3.get_data().isApprox(data));
}

TEST_F(ControlInputTest, InvalidConstruction) {
  ASSERT_THROW(ControlInput(-1), std::invalid_argument);
}

TEST_F(ControlInputTest, ConstControlInput) {
  // For a const ControlInput, the values can only be accessed but not set, as a
  // reference (lvalue) is not returned for this overload of the operator.

  const ControlInput control_input(3);

  ASSERT_EQ(control_input.get_size(), 3);
  ASSERT_TRUE(control_input.get_data().isApprox(VectorXd::Zero(3)));

  // Making sure position accessing works.
  for (int i = 0; i < control_input.get_size(); ++i) {
    ASSERT_EQ(control_input[i], 0);
  }

  // After const casting, we should be able to modify the data.
  const_cast<ControlInput &>(control_input).set_data(VectorXd::Ones(3));
  ASSERT_TRUE(control_input.get_data().isApprox(VectorXd::Ones(3)));
}

TEST_F(ControlInputTest, EmptyConstruction) {
  ControlInput control_input(0);

  // Assert emptiness.
  ASSERT_TRUE(control_input.IsEmpty());
  ASSERT_TRUE(ControlInput(VectorXd::Zero(0)).IsEmpty());
  ASSERT_TRUE(ControlInput{}.IsEmpty());

  // Accessors are invalid for empty ControlInput
  ASSERT_THROW(control_input.get_data(), std::logic_error);
  ASSERT_THROW(control_input[0], std::logic_error);
  ASSERT_THROW(control_input.set_data(VectorXd::Random(0)), std::logic_error);
}

TEST_F(ControlInputTest, Sizes) {
  ASSERT_EQ(control_input1_->get_size(), 3);
  ASSERT_EQ(control_input2_->get_size(), 4);
  ASSERT_EQ(control_input3_->get_size(), 5);

  // Empty ControlInput.
  ASSERT_EQ(ControlInput(0).get_size(), 0);
}

TEST_F(ControlInputTest, GetData) {
  ASSERT_TRUE(control_input1_->get_data().isApprox(VectorXd::Zero(3)));
  ASSERT_TRUE(control_input2_->get_data().isApprox(VectorXd::Zero(4)));
  ASSERT_TRUE(control_input3_->get_data().isApprox(VectorXd::Zero(5)));

  VectorXd data = VectorXd::Random(6);
  ControlInput control_input(data);

  ASSERT_TRUE(control_input.get_data().isApprox(data));
}

TEST_F(ControlInputTest, GetControlInputAt) {
  for (int i = 0; i < control_input1_->get_size(); ++i) {
    ASSERT_EQ((*control_input1_)[i], 0);
  }
  for (int i = 0; i < control_input2_->get_size(); ++i) {
    ASSERT_EQ((*control_input2_)[i], 0);
  }
  for (int i = 0; i < control_input3_->get_size(); ++i) {
    ASSERT_EQ((*control_input3_)[i], 0);
  }

  // Arbitrary ControlInput.
  VectorXd data = VectorXd::Random(7);
  ControlInput control_input(data);

  for (int i = 0; i < control_input.get_size(); ++i) {
    ASSERT_EQ(control_input[i], data(i));
  }

  // Invalid get at.
  ASSERT_THROW((*control_input1_)[-1], std::out_of_range);
  ASSERT_THROW((*control_input1_)[3], std::out_of_range);

  ASSERT_THROW((*control_input2_)[-1], std::out_of_range);
  ASSERT_THROW((*control_input2_)[4], std::out_of_range);

  ASSERT_THROW((*control_input3_)[-1], std::out_of_range);
  ASSERT_THROW((*control_input3_)[5], std::out_of_range);
}

TEST_F(ControlInputTest, SetData) {
  VectorXd data = VectorXd::Random(4);
  VectorXd expected_data(5);
  expected_data << 1, 0, -1, 2.5, 0;

  control_input1_->set_data(VectorXd::Ones(3));
  control_input2_->set_data(data);
  control_input3_->set_data({1, 0, -1, 2.5, 0});

  ASSERT_TRUE(control_input1_->get_data().isApprox(VectorXd::Ones(3)));
  ASSERT_TRUE(control_input2_->get_data().isApprox(data));
  ASSERT_TRUE(control_input3_->get_data().isApprox(expected_data));

  // Invalid set data.
  ASSERT_THROW(control_input1_->set_data(VectorXd::Ones(2)),
               std::invalid_argument);
  ASSERT_THROW(control_input2_->set_data(VectorXd::Ones(5)),
               std::invalid_argument);
  ASSERT_THROW(control_input3_->set_data({}), std::invalid_argument);
  ASSERT_THROW(control_input3_->set_data({1, 2, 3, 4}), std::invalid_argument);
  ASSERT_THROW(control_input3_->set_data({1, 2, 1, 2, 1, 2}),
               std::invalid_argument);
}

TEST_F(ControlInputTest, SetControlInputAt) {
  for (int i = 0; i < control_input1_->get_size(); ++i) {
    (*control_input1_)[i] = 1;
  }
  for (int i = 0; i < control_input2_->get_size(); ++i) {
    (*control_input2_)[i] = 2;
  }
  for (int i = 0; i < control_input3_->get_size(); ++i) {
    (*control_input3_)[i] = -3;
  }

  ASSERT_TRUE(control_input1_->get_data().isApprox(VectorXd::Ones(3)));
  ASSERT_TRUE(control_input2_->get_data().isApprox(2 * VectorXd::Ones(4)));
  ASSERT_TRUE(control_input3_->get_data().isApprox(-3 * VectorXd::Ones(5)));

  // Invalid set at.
  ASSERT_THROW((*control_input1_)[-1] = 0, std::out_of_range);
  ASSERT_THROW((*control_input1_)[3] = 1, std::out_of_range);

  ASSERT_THROW((*control_input2_)[-1] = 0, std::out_of_range);
  ASSERT_THROW((*control_input2_)[4] = 1, std::out_of_range);

  ASSERT_THROW((*control_input3_)[-1] = 0, std::out_of_range);
  ASSERT_THROW((*control_input3_)[5] = 1, std::out_of_range);
}

TEST_F(ControlInputTest, Addition) {
  VectorXd i1(3), i2(3), d1(3), d2(3);
  i1 << 1, 2, 3;
  i2 << 4, -5, 6;
  d1 << 5, -3, 9;
  d2 << 9, -8, 15;

  ControlInput control_input1{1, 2, 3};
  ControlInput control_input2(i2);

  // Trivial addition.
  control_input1 += ControlInput::CreateLike(control_input1);
  ASSERT_TRUE(control_input1.get_data().isApprox(i1));

  control_input1 = control_input1 + ControlInput::CreateLike(control_input1);
  ASSERT_TRUE(control_input1.get_data().isApprox(i1));

  control_input1 += control_input2;
  ASSERT_TRUE(control_input1.get_data().isApprox(d1));

  // Commutativity.
  ControlInput control_input3 = control_input1 + control_input2;
  ASSERT_TRUE(control_input3.get_data().isApprox(d2));

  ControlInput control_input4 = control_input2 + control_input1;
  ASSERT_TRUE(control_input3.get_data().isApprox(control_input4.get_data()));

  // Empty addition.
  ControlInput empty_control_input1(0), empty_control_input2{};

  ControlInput empty_control_input_add =
      empty_control_input1 + empty_control_input2;
  ASSERT_TRUE(empty_control_input_add.IsEmpty());
}

TEST_F(ControlInputTest, Subtraction) {
  VectorXd i1(3), i2(3), d1(3), d2(3);
  i1 << 1, 2, 3;
  i2 << 4, -5, 6;
  d1 << -3, 7, -3;
  d2 << -7, 12, -9;

  ControlInput control_input1({1, 2, 3});
  ControlInput control_input2(i2);

  // Trivial subtraction.
  control_input1 -= ControlInput::CreateLike(control_input1);
  ASSERT_TRUE(control_input1.get_data().isApprox(i1));

  control_input1 = control_input1 - ControlInput::CreateLike(control_input1);
  ASSERT_TRUE(control_input1.get_data().isApprox(i1));

  control_input1 -= control_input2;
  ASSERT_TRUE(control_input1.get_data().isApprox(d1));

  ControlInput control_input3 = control_input1 - control_input2;
  ASSERT_TRUE(control_input3.get_data().isApprox(d2));

  ControlInput control_input4 = control_input2 - control_input1;
  ASSERT_TRUE(
      control_input3.get_data().isApprox(-1 * control_input4.get_data()));

  // Empty subtraction.
  ControlInput empty_control_input1(0), empty_control_input2{};

  ControlInput empty_control_input_sub =
      empty_control_input1 - empty_control_input2;
  ASSERT_TRUE(empty_control_input_sub.IsEmpty());
}

TEST_F(ControlInputTest, Multiplication) {
  VectorXd i1(3), i2(3), d1(3), d2(3);
  i1 << 1, 2, 3;
  i2 << 4, -5, 6;
  d1 << 2, 4, 6;
  d2 << -6, 7.5, -9;

  ControlInput control_input1({1, 2, 3});
  ControlInput control_input2(i2);

  // Trivial multiplication.
  control_input1 = control_input1 * 1.0;
  ASSERT_TRUE(control_input1.get_data().isApprox(i1));
  ASSERT_TRUE((0.0 * control_input1).get_data().isApprox(VectorXd::Zero(3)));

  control_input1 *= 2.0;
  ASSERT_TRUE(control_input1.get_data().isApprox(d1));

  // Commutativity.
  ControlInput control_input3 = control_input2 * -1.5;
  ControlInput control_input4 = -1.5 * control_input2;
  ASSERT_TRUE(control_input3.get_data().isApprox(d2));
  ASSERT_TRUE(control_input4.get_data().isApprox(d2));

  // Empty multiplication.
  ControlInput empty_control_input1(0), empty_control_input2{};

  ControlInput empty_control_input_mult1 = empty_control_input1 * 7.0;
  ControlInput empty_control_input_mult2 = empty_control_input2 * 7.0;
  ASSERT_TRUE(empty_control_input_mult1.IsEmpty());
  ASSERT_TRUE(empty_control_input_mult2.IsEmpty());
}

TEST_F(ControlInputTest, Equality) {
  ASSERT_TRUE(ControlInput(3) == ControlInput(3));
  ASSERT_TRUE(ControlInput(3) == ControlInput(VectorXd::Zero(3)));
  ASSERT_TRUE(ControlInput(VectorXd::Ones(2)) == ControlInput({1, 1}));
  ASSERT_TRUE(ControlInput({1, 2}) == ControlInput({1, 2}));
}

TEST_F(ControlInputTest, Inequality) {
  ASSERT_TRUE(ControlInput(3) != ControlInput(2));
  ASSERT_TRUE(ControlInput(3) != ControlInput(VectorXd::Zero(2)));
  ASSERT_TRUE(ControlInput(2) != ControlInput({0}));
  ASSERT_TRUE(ControlInput({1, 2}) != ControlInput({3, 4}));
  // Inequality for one digit more than the precision.
  ASSERT_TRUE(ControlInput({1, 2}) != ControlInput({1, 2.00001}));
}

TEST_F(ControlInputTest, StringRepresentation) {
  // Testing that the << operator is overloaded properly.
  // We don't test the actual string representation.
  ostringstream os;
  os << (*control_input1_);

  // Multiple ControlInput object representations in the stream.
  os << " " << (*control_input2_) << std::endl;
}

TEST_F(ControlInputTest, CreateLike) {
  ControlInput control_input1 = ControlInput::CreateLike(*control_input1_);
  ControlInput control_input2 = ControlInput::CreateLike(*control_input2_);
  ControlInput control_input3 = ControlInput::CreateLike(*control_input3_);

  ASSERT_EQ(control_input1.get_size(), 3);
  ASSERT_TRUE(control_input1.get_data().isApprox(VectorXd::Zero(3)));

  ASSERT_EQ(control_input2.get_size(), 4);
  ASSERT_TRUE(control_input2.get_data().isApprox(VectorXd::Zero(4)));

  ASSERT_EQ(control_input3.get_size(), 5);
  ASSERT_TRUE(control_input3.get_data().isApprox(VectorXd::Zero(5)));
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
