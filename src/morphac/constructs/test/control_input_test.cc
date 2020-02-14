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

TEST_F(ControlInputTest, Addition) {
  VectorXd v1(3), v2(3), q1(3), q2(3);
  v1 << 1, 2, 3;
  v2 << 4, 5, 6;
  q1 << 5, 7, 9;
  q2 << 9, 12, 15;

  ControlInput input1(v1);
  ControlInput input2(v2);
  input1 += input2;
  ASSERT_TRUE(input1.get_input_vector().isApprox(q1));

  ControlInput input3 = input1 + input2;
  ASSERT_TRUE(input3.get_input_vector().isApprox(q2));

  ControlInput input4 = input2 + input1;
  ASSERT_TRUE(input3.get_input_vector().isApprox(input4.get_input_vector()));
}

TEST_F(ControlInputTest, Subtraction) {
  VectorXd v1(3), v2(3), q1(3), q2(3);
  v1 << 1, 2, 3;
  v2 << 4, 5, 6;
  q1 << -3, -3, -3;
  q2 << -7, -8, -9;

  ControlInput input1(v1);
  ControlInput input2(v2);
  input1 -= input2;
  ASSERT_TRUE(input1.get_input_vector().isApprox(q1));

  ControlInput input3 = input1 - input2;
  ASSERT_TRUE(input3.get_input_vector().isApprox(q2));

  ControlInput input4 = input2 - input1;
  ASSERT_TRUE(input3.get_input_vector().isApprox(-1 * input4.get_input_vector()));
}

TEST_F(ControlInputTest, Multiplication) {
  VectorXd v1(3), v2(3), q1(3), q2(3);
  v1 << 1, 2, 3;
  v2 << 4, 5, 6;
  q1 << 2, 4, 6;
  q2 << -4, -5, -6;

  ControlInput input1(v1);
  ControlInput input2(v2);

  input1 *= 2.0;
  ASSERT_TRUE(input1.get_input_vector().isApprox(q1));

  ControlInput input3 = input2 * -1.0;
  ControlInput input4 = -1 * input2;
  ASSERT_TRUE(input3.get_input_vector().isApprox(q2));
  ASSERT_TRUE(input4.get_input_vector().isApprox(q2));
}



}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
