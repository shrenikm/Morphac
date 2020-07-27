#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "constructs/include/velocity.h"

namespace {

using std::initializer_list;
using std::make_unique;
using std::ostringstream;
using std::srand;
using std::unique_ptr;

using Eigen::VectorXd;

using morphac::constructs::Velocity;

class VelocityTest : public ::testing::Test {
 protected:
  VelocityTest() {
    // Set random seed for Eigen.
    srand(7);
    velocity1_ = make_unique<Velocity>(3);
    velocity2_ = make_unique<Velocity>(VectorXd::Zero(4));
    velocity3_ = make_unique<Velocity>(initializer_list<double>{0, 0, 0, 0, 0});
  }

  void SetUp() override {}

  unique_ptr<Velocity> velocity1_, velocity2_, velocity3_;
};

TEST_F(VelocityTest, CopyConstructor) {
  Velocity velocity1(*velocity1_);

  VectorXd data = VectorXd::Random(4);
  Velocity velocity2(data);
  Velocity velocity3(velocity2);

  ASSERT_TRUE(velocity1.get_data().isApprox(VectorXd::Zero(3)));
  ASSERT_TRUE(velocity3.get_data().isApprox(data));
}

TEST_F(VelocityTest, CopyAssignment) {
  Velocity velocity1 = *velocity1_;

  VectorXd data = VectorXd::Random(4);
  Velocity velocity2(data);
  Velocity velocity3 = velocity2;

  ASSERT_TRUE(velocity1.get_data().isApprox(VectorXd::Zero(3)));
  ASSERT_TRUE(velocity3.get_data().isApprox(data));
}

TEST_F(VelocityTest, InvalidConstruction) {
  ASSERT_THROW(Velocity(-1), std::invalid_argument);
}

TEST_F(VelocityTest, ConstVelocity) {
  // For a const Velocity, the values can only be accessed but not set, as a
  // reference (lvalue) is not returned for this overload of the operator.

  const Velocity velocity(3);

  ASSERT_EQ(velocity.get_size(), 3);
  ASSERT_TRUE(velocity.get_data().isApprox(VectorXd::Zero(3)));

  // Making sure position accessing works.
  for (int i = 0; i < velocity.get_size(); ++i) {
    ASSERT_EQ(velocity[i], 0);
  }

  // After const casting, we should be able to modify the data.
  const_cast<Velocity &>(velocity).set_data(VectorXd::Ones(3));
  ASSERT_TRUE(velocity.get_data().isApprox(VectorXd::Ones(3)));
}

TEST_F(VelocityTest, EmptyConstruction) {
  Velocity velocity(0);

  // Assert emptiness.
  ASSERT_TRUE(velocity.IsEmpty());
  ASSERT_TRUE(Velocity(VectorXd::Zero(0)).IsEmpty());
  ASSERT_TRUE(Velocity{}.IsEmpty());

  // Accessors are invalid for empty Velocity
  ASSERT_THROW(velocity.get_data(), std::logic_error);
  ASSERT_THROW(velocity[0], std::logic_error);
  ASSERT_THROW(velocity.set_data(VectorXd::Random(0)), std::logic_error);
}

TEST_F(VelocityTest, Sizes) {
  ASSERT_EQ(velocity1_->get_size(), 3);
  ASSERT_EQ(velocity2_->get_size(), 4);
  ASSERT_EQ(velocity3_->get_size(), 5);

  // Empty Velocity.
  ASSERT_EQ(Velocity(0).get_size(), 0);
}

TEST_F(VelocityTest, GetData) {
  ASSERT_TRUE(velocity1_->get_data().isApprox(VectorXd::Zero(3)));
  ASSERT_TRUE(velocity2_->get_data().isApprox(VectorXd::Zero(4)));
  ASSERT_TRUE(velocity3_->get_data().isApprox(VectorXd::Zero(5)));

  VectorXd data = VectorXd::Random(6);
  Velocity velocity(data);

  ASSERT_TRUE(velocity.get_data().isApprox(data));
}

TEST_F(VelocityTest, GetVelocityAt) {
  for (int i = 0; i < velocity1_->get_size(); ++i) {
    ASSERT_EQ((*velocity1_)[i], 0);
  }
  for (int i = 0; i < velocity2_->get_size(); ++i) {
    ASSERT_EQ((*velocity2_)[i], 0);
  }
  for (int i = 0; i < velocity3_->get_size(); ++i) {
    ASSERT_EQ((*velocity3_)[i], 0);
  }

  // Arbitrary Velocity.
  VectorXd data = VectorXd::Random(7);
  Velocity velocity(data);

  for (int i = 0; i < velocity.get_size(); ++i) {
    ASSERT_EQ(velocity[i], data(i));
  }

  // Invalid get at.
  ASSERT_THROW((*velocity1_)[-1], std::out_of_range);
  ASSERT_THROW((*velocity1_)[3], std::out_of_range);

  ASSERT_THROW((*velocity2_)[-1], std::out_of_range);
  ASSERT_THROW((*velocity2_)[4], std::out_of_range);

  ASSERT_THROW((*velocity3_)[-1], std::out_of_range);
  ASSERT_THROW((*velocity3_)[5], std::out_of_range);
}

TEST_F(VelocityTest, SetData) {
  VectorXd data = VectorXd::Random(4);
  VectorXd expected_data(5);
  expected_data << 1, 0, -1, 2.5, 0;

  velocity1_->set_data(VectorXd::Ones(3));
  velocity2_->set_data(data);
  velocity3_->set_data({1, 0, -1, 2.5, 0});

  ASSERT_TRUE(velocity1_->get_data().isApprox(VectorXd::Ones(3)));
  ASSERT_TRUE(velocity2_->get_data().isApprox(data));
  ASSERT_TRUE(velocity3_->get_data().isApprox(expected_data));

  // Invalid set data.
  ASSERT_THROW(velocity1_->set_data(VectorXd::Ones(2)), std::invalid_argument);
  ASSERT_THROW(velocity2_->set_data(VectorXd::Ones(5)), std::invalid_argument);
  ASSERT_THROW(velocity3_->set_data({}), std::invalid_argument);
  ASSERT_THROW(velocity3_->set_data({1, 2, 3, 4}), std::invalid_argument);
  ASSERT_THROW(velocity3_->set_data({1, 2, 1, 2, 1, 2}), std::invalid_argument);
}

TEST_F(VelocityTest, SetVelocityAt) {
  for (int i = 0; i < velocity1_->get_size(); ++i) {
    (*velocity1_)[i] = 1;
  }
  for (int i = 0; i < velocity2_->get_size(); ++i) {
    (*velocity2_)[i] = 2;
  }
  for (int i = 0; i < velocity3_->get_size(); ++i) {
    (*velocity3_)[i] = -3.;
  }

  ASSERT_TRUE(velocity1_->get_data().isApprox(VectorXd::Ones(3)));
  ASSERT_TRUE(velocity2_->get_data().isApprox(2 * VectorXd::Ones(4)));
  ASSERT_TRUE(velocity3_->get_data().isApprox(-3 * VectorXd::Ones(5)));

  // Invalid set at.
  ASSERT_THROW((*velocity1_)[-1] = 0, std::out_of_range);
  ASSERT_THROW((*velocity1_)[3] = 1, std::out_of_range);

  ASSERT_THROW((*velocity2_)[-1] = 0, std::out_of_range);
  ASSERT_THROW((*velocity2_)[4] = 1, std::out_of_range);

  ASSERT_THROW((*velocity3_)[-1] = 0, std::out_of_range);
  ASSERT_THROW((*velocity3_)[5] = 1, std::out_of_range);
}

TEST_F(VelocityTest, Addition) {
  VectorXd v1(3), v2(3), d1(3), d2(3);
  v1 << 1, 2, 3;
  v2 << 4, -5, 6;
  d1 << 5, -3, 9;
  d2 << 9, -8, 15;

  Velocity velocity1{1, 2, 3};
  Velocity velocity2(v2);

  // Trivial addition.
  velocity1 += Velocity::CreateLike(velocity1);
  ASSERT_TRUE(velocity1.get_data().isApprox(v1));

  velocity1 = velocity1 + Velocity::CreateLike(velocity1);
  ASSERT_TRUE(velocity1.get_data().isApprox(v1));

  velocity1 += velocity2;
  ASSERT_TRUE(velocity1.get_data().isApprox(d1));

  // Commutativity.
  Velocity velocity3 = velocity1 + velocity2;
  ASSERT_TRUE(velocity3.get_data().isApprox(d2));

  Velocity velocity4 = velocity2 + velocity1;
  ASSERT_TRUE(velocity3.get_data().isApprox(velocity4.get_data()));

  // Empty addition.
  Velocity empty_velocity1(0), empty_velocity2{};

  Velocity empty_velocity_add = empty_velocity1 + empty_velocity2;
  ASSERT_TRUE(empty_velocity_add.IsEmpty());
}

TEST_F(VelocityTest, Subtraction) {
  VectorXd v1(3), v2(3), d1(3), d2(3);
  v1 << 1, 2, 3;
  v2 << 4, -5, 6;
  d1 << -3, 7, -3;
  d2 << -7, 12, -9;

  Velocity velocity1({1, 2, 3});
  Velocity velocity2(v2);

  // Trivial subtraction.
  velocity1 -= Velocity::CreateLike(velocity1);
  ASSERT_TRUE(velocity1.get_data().isApprox(v1));

  velocity1 = velocity1 - Velocity::CreateLike(velocity1);
  ASSERT_TRUE(velocity1.get_data().isApprox(v1));

  velocity1 -= velocity2;
  ASSERT_TRUE(velocity1.get_data().isApprox(d1));

  Velocity velocity3 = velocity1 - velocity2;
  ASSERT_TRUE(velocity3.get_data().isApprox(d2));

  Velocity velocity4 = velocity2 - velocity1;
  ASSERT_TRUE(velocity3.get_data().isApprox(-1 * velocity4.get_data()));

  // Empty subtraction.
  Velocity empty_velocity1(0), empty_velocity2{};

  Velocity empty_velocity_sub = empty_velocity1 - empty_velocity2;
  ASSERT_TRUE(empty_velocity_sub.IsEmpty());
}

TEST_F(VelocityTest, Multiplication) {
  VectorXd v1(3), v2(3), d1(3), d2(3);
  v1 << 1, 2, 3;
  v2 << 4, -5, 6;
  d1 << 2, 4, 6;
  d2 << -6, 7.5, -9;

  Velocity velocity1({1, 2, 3});
  Velocity velocity2(v2);

  // Trivial multiplication.
  velocity1 = velocity1 * 1.0;
  ASSERT_TRUE(velocity1.get_data().isApprox(v1));
  ASSERT_TRUE((0.0 * velocity1).get_data().isApprox(VectorXd::Zero(3)));

  velocity1 *= 2.0;
  ASSERT_TRUE(velocity1.get_data().isApprox(d1));

  // Commutativity.
  Velocity velocity3 = velocity2 * -1.5;
  Velocity velocity4 = -1.5 * velocity2;
  ASSERT_TRUE(velocity3.get_data().isApprox(d2));
  ASSERT_TRUE(velocity4.get_data().isApprox(d2));

  // Empty multiplication.
  Velocity empty_velocity1(0), empty_velocity2{};

  Velocity empty_velocity_mult1 = empty_velocity1 * 7.0;
  Velocity empty_velocity_mult2 = empty_velocity2 * 7.0;
  ASSERT_TRUE(empty_velocity_mult1.IsEmpty());
  ASSERT_TRUE(empty_velocity_mult2.IsEmpty());
}

TEST_F(VelocityTest, Equality) {
  ASSERT_TRUE(Velocity(3) == Velocity(3));
  ASSERT_TRUE(Velocity(3) == Velocity(VectorXd::Zero(3)));
  ASSERT_TRUE(Velocity(VectorXd::Ones(2)) == Velocity({1, 1}));
  ASSERT_TRUE(Velocity({1, 2}) == Velocity({1, 2}));

  ASSERT_TRUE(Velocity(3) != Velocity(2));
  ASSERT_TRUE(Velocity(3) != Velocity(VectorXd::Zero(2)));
  ASSERT_TRUE(Velocity(2) != Velocity({0}));
  ASSERT_TRUE(Velocity({1, 2}) != Velocity({3, 4}));
  // Inequality for one digit more than the precision.
  ASSERT_TRUE(Velocity({1, 2}) != Velocity({1, 2.00001}));
}

TEST_F(VelocityTest, StringRepresentation) {
  // Testing that the << operator is overloaded properly.
  // We don't test the actual string representation.
  ostringstream os;
  os << (*velocity1_);

  // Multiple velocity object representations in the stream.
  os << " " << (*velocity2_) << std::endl;
}

TEST_F(VelocityTest, CreateLike) {
  Velocity velocity1 = Velocity::CreateLike(*velocity1_);
  Velocity velocity2 = Velocity::CreateLike(*velocity2_);
  Velocity velocity3 = Velocity::CreateLike(*velocity3_);

  ASSERT_EQ(velocity1.get_size(), 3);
  ASSERT_TRUE(velocity1.get_data().isApprox(VectorXd::Zero(3)));

  ASSERT_EQ(velocity2.get_size(), 4);
  ASSERT_TRUE(velocity2.get_data().isApprox(VectorXd::Zero(4)));

  ASSERT_EQ(velocity3.get_size(), 5);
  ASSERT_TRUE(velocity3.get_data().isApprox(VectorXd::Zero(5)));
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
