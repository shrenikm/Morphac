#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "robot/blueprint/include/robot2D.h"

namespace {

using Eigen::VectorXd;
using Eigen::MatrixXd;

using std::make_shared;
using std::shared_ptr;
using std::string;

using morphac::constructs::ControlInput;
using morphac::constructs::Pose;
using morphac::constructs::State;
using morphac::constructs::Velocity;
using morphac::mechanics::models::KinematicModel;
using morphac::robot::blueprint::Footprint2D;
using morphac::robot::blueprint::Robot2D;

class SomeKinematicModel : public KinematicModel {
 public:
  SomeKinematicModel(string name, int size_pose, int size_velocity,
                     int size_input)
      : KinematicModel(name, size_pose, size_velocity, size_input) {}

  void ComputeStateDerivative(const State& state, const ControlInput& input,
                              State& derivative) const {
    // f(x, u) = x * u  - x
    VectorXd derivative_vector(state.get_size());
    derivative_vector << state.get_state_vector();
    derivative_vector =
        (derivative_vector.array() * input.get_input_vector().array() -
         derivative_vector.array())
            .matrix();
    derivative.set_pose_vector(derivative_vector.head(size_pose));
    derivative.set_velocity_vector(derivative_vector.tail(size_velocity));
  }

  State ComputeStateDerivative(const State& state,
                               const ControlInput& input) const {
    State derivative(size_pose, size_velocity);
    ComputeStateDerivative(state, input, derivative);
    return derivative;
  }
};

class Robot2DTest : public ::testing::Test {
 protected:
  Robot2DTest() {}

  void SetUp() override {
    pose_vector_ = VectorXd::Random(3);
    velocity_vector_ = VectorXd::Random(2);
    input_vector_ = VectorXd::Random(5);
    footprint_matrix_ = MatrixXd::Random(10, 2);
  }

  VectorXd pose_vector_, velocity_vector_, input_vector_;
  MatrixXd footprint_matrix_;
};

TEST_F(Robot2DTest, Construction) {
  SomeKinematicModel model("model", 3, 2, 5);
  Footprint2D footprint(footprint_matrix_);
  Robot2D robot1{"robot1", model, footprint};

  Robot2D robot2{"robot2", model, footprint, State(3, 2)};
}

TEST_F(Robot2DTest, InvalidConstruction) {
  SomeKinematicModel model("model", 3, 2, 5);
  Footprint2D footprint(footprint_matrix_);
  ASSERT_THROW(Robot2D("robot", model, footprint, State(4, 3)),
               std::invalid_argument);
}

TEST_F(Robot2DTest, Accessors) {
  SomeKinematicModel model("model", 3, 2, 5);
  Footprint2D footprint(footprint_matrix_);
  Robot2D robot1{"robot1", model, footprint};

  VectorXd initial_pose{VectorXd::Random(3)};
  VectorXd initial_velocity{VectorXd::Random(2)};
  VectorXd initial_state(5);
  initial_state << initial_pose, initial_velocity;
  Robot2D robot2{"robot2", model, footprint,
                 State(initial_pose, initial_velocity)};

  ASSERT_EQ(robot1.get_name(), "robot1");
  ASSERT_EQ(robot2.get_name(), "robot2");

  // Making sure that the initial state is correct.
  // For the robot object created without initial state, the initial pose and
  // velocity must be zero. For the case with an explicit initial state, it must
  // match the given initial state.
  ASSERT_TRUE(
      robot1.get_state().get_state_vector().isApprox(VectorXd::Zero(5)));
  ASSERT_TRUE(robot1.get_pose().get_pose_vector().isApprox(VectorXd::Zero(3)));
  ASSERT_TRUE(
      robot1.get_velocity().get_velocity_vector().isApprox(VectorXd::Zero(2)));

  ASSERT_TRUE(robot2.get_state().get_state_vector().isApprox(initial_state));
  ASSERT_TRUE(robot2.get_state().get_pose_vector().isApprox(initial_pose));
  ASSERT_TRUE(
      robot2.get_state().get_velocity_vector().isApprox(initial_velocity));
}

TEST_F(Robot2DTest, Derivative) {
  SomeKinematicModel model("model", 3, 2, 5);
  Footprint2D footprint(footprint_matrix_);
  VectorXd initial_pose(3), initial_velocity(2), input(5),
      expected_state_derivative(5);
  initial_pose << 1, 1, -2;
  initial_velocity << 3, -5;
  input << 1, 2, 3, 2, 1;
  expected_state_derivative << 0, 1, -4, 3, 0;
  Robot2D robot{"robot", model, footprint,
                State(initial_pose, initial_velocity)};

  State derivative1{3, 2};
  robot.ComputeStateDerivative(input, derivative1);

  ASSERT_TRUE(
      derivative1.get_state_vector().isApprox(expected_state_derivative));

  input(2) = 2;
  expected_state_derivative(2) = -2;
  State derivative2 = robot.ComputeStateDerivative(input);
  ASSERT_TRUE(
      derivative2.get_state_vector().isApprox(expected_state_derivative));
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

