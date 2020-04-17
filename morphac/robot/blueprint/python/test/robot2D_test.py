import numpy as np
import pytest

from morphac.constructs import Pose, Input, State, Velocity
from morphac.mechanics.models import (
    KinematicModel,
    DiffDriveModel,
    TricycleModel
)
from morphac.robot.blueprint import Footprint2D, Robot2D

# KinematicModel extension class to ensure that a robot can be created from
# a subclassed KinematicModel


class NewKinematicModel(KinematicModel):

    def __init__(self, sp, sv, si, a, b):

        KinematicModel.__init__(self,  sp, sv, si)
        self.a = a
        self.b = b

    def compute_state_derivative(self, robot_state, robot_input):

        tmp_der = np.sum(np.multiply(robot_state.data, robot_input.data))
        tmp_der = tmp_der + self.a * self.b
        # tmp_der is a scalar, but the derivative must be a State object.
        # Copying tmp_der to each State element.
        der = State([tmp_der] * self.size_pose, [tmp_der] * self.size_velocity)
        return der


@pytest.fixture()
def generate_robot2D_list():

    r1 = Robot2D("r1", DiffDriveModel(1, 1), Footprint2D([[1, 2]]))
    r2 = Robot2D("r2", TricycleModel(1, 1),
                 Footprint2D(np.ones([20, 2])))
    r3 = Robot2D("r3", NewKinematicModel(3, 2, 5, 2.5, 2),
                 Footprint2D([[1, 0], [0, 1]]))
    r4 = Robot2D(name="r4",
                 kinematic_model=NewKinematicModel(2, 2, 4, 0, 0),
                 footprint=Footprint2D([[0, 0]]),
                 initial_state=State([1, 2], [3, 4])
                 )

    return r1, r2, r3, r4


def test_name(generate_robot2D_list):

    r1, r2, r3, r4 = generate_robot2D_list

    assert r1.name == "r1"
    assert r2.name == "r2"
    assert r3.name == "r3"
    assert r4.name == "r4"

    # Making sure that the name is read only.
    with pytest.raises(AttributeError):
        r1.name = "r2"


def test_kinematic_model(generate_robot2D_list):

    r1, r2, r3, r4 = generate_robot2D_list

    # Making sure that they are of the right type.
    assert isinstance(r1.kinematic_model, DiffDriveModel)
    assert isinstance(r2.kinematic_model, TricycleModel)
    assert isinstance(r3.kinematic_model, NewKinematicModel)
    assert isinstance(r4.kinematic_model, NewKinematicModel)

    # Testing the actual model details.
    assert r1.kinematic_model.size_pose == 3
    assert r2.kinematic_model.size_pose == 4
    assert r3.kinematic_model.size_pose == 3
    assert r4.kinematic_model.size_pose == 2

    assert r1.kinematic_model.size_velocity == 0
    assert r2.kinematic_model.size_velocity == 0
    assert r3.kinematic_model.size_velocity == 2
    assert r4.kinematic_model.size_velocity == 2

    assert r1.kinematic_model.size_input == 2
    assert r2.kinematic_model.size_input == 2
    assert r3.kinematic_model.size_input == 5
    assert r4.kinematic_model.size_input == 4

    assert r1.kinematic_model.radius == 1
    assert r1.kinematic_model.length == 1
    assert r2.kinematic_model.radius == 1
    assert r2.kinematic_model.length == 1
    assert r3.kinematic_model.a == 2.5
    assert r3.kinematic_model.b == 2
    assert r4.kinematic_model.a == 0
    assert r4.kinematic_model.b == 0

    # Making sure that the kinematic model is read only.
    with pytest.raises(AttributeError):
        r1.kinematic_model = TricycleModel(2, 2)
    with pytest.raises(AttributeError):
        r2.kinematic_model = TricycleModel(1, 1)


def test_footprint(generate_robot2D_list):

    r1, r2, r3, r4 = generate_robot2D_list

    assert np.allclose(r1.footprint.data, [[1, 2]])
    assert np.allclose(r2.footprint.data, np.ones([20, 2]))
    assert np.allclose(r3.footprint.data, [[1, 0], [0, 1]])
    assert np.allclose(r4.footprint.data, [[0, 0]])

    # Making sure that footprint is read only.
    with pytest.raises(AttributeError):
        r1.footprint = [[1, 2], [3, 4], [5, 6]]
    with pytest.raises(AttributeError):
        r2.footprint = np.ones([20, 2])


def test_state(generate_robot2D_list):

    r1, r2, r3, r4 = generate_robot2D_list

    # r1, r2, r3 have not been created using an initial state and must hence
    # be zero.
    assert np.allclose(r1.state.data, [0, 0, 0])
    assert np.allclose(r2.state.data, [0, 0, 0, 0])
    assert np.allclose(r3.state.data, [0, 0, 0, 0, 0])
    # r4 has an initial state.
    assert np.allclose(r4.state.data, [1, 2, 3, 4])

    # Test state setting.
    r1.state = State([1, 1, 1], [])
    r3.state.data = [1, 1, 2, 3, 5]

    assert np.allclose(r1.state.data, [1, 1, 1])
    assert np.allclose(r3.state.data, [1, 1, 2, 3, 5])

    # State operations.
    r1.state -= State([0, 1, 0], [])
    r3.state = r3.state + State([1, 1, 1], [1, 1])
    assert np.allclose(r1.state.data, [1, 0, 1])
    assert np.allclose(r3.state.data, [2, 2, 3, 4, 6])

    r1.state *= 3
    r3.state = -10 * r3.state
    assert np.allclose(r1.state.data, [3, 0, 3])
    assert np.allclose(r3.state.data, [-20, -20, -30, -40, -60])


def test_pose(generate_robot2D_list):

    r1, r2, r3, r4 = generate_robot2D_list

    assert np.allclose(r1.pose.data, [0, 0, 0])
    assert np.allclose(r2.pose.data, [0, 0, 0, 0])
    assert np.allclose(r3.pose.data, [0, 0, 0])
    assert np.allclose(r4.pose.data, [1, 2])

    # Test pose setting.
    r1.pose = Pose([2, 2, 2])
    r3.pose = Pose([1, 1, 1])

    # Also making sure that the velocity component has not changed.
    assert np.allclose(r1.pose.data, [2, 2, 2])
    assert np.allclose(r3.pose.data, [1, 1, 1])
    assert np.allclose(r1.state.data, [2, 2, 2])
    assert np.allclose(r3.state.data, [1, 1, 1, 0, 0])

    # Pose operations.
    r1.pose -= Pose([1, 1, 1])
    r3.pose = r3.pose + Pose([1, 1, 1])
    assert np.allclose(r1.pose.data, [1, 1, 1])
    assert np.allclose(r3.pose.data, [2, 2, 2])
    assert np.allclose(r1.state.data, [1, 1, 1])
    assert np.allclose(r3.state.data, [2, 2, 2, 0, 0])

    r1.pose *= 2
    r3.pose = -1 * r3.pose
    assert np.allclose(r1.pose.data, [2, 2, 2])
    assert np.allclose(r3.pose.data, [-2, -2, -2])
    assert np.allclose(r1.state.data, [2, 2, 2])
    assert np.allclose(r3.state.data, [-2, -2, -2, 0, 0])


def test_velocity(generate_robot2D_list):

    r1, r2, r3, r4 = generate_robot2D_list

    assert np.allclose(r3.velocity.data, [0, 0])
    assert np.allclose(r4.velocity.data, [3, 4])

    # Test velocity setting.
    r3.velocity = Velocity([1, 1])
    r4.velocity = Velocity([0, 0])

    # Also making sure that the pose component has not changed.
    assert np.allclose(r3.velocity.data, [1, 1])
    assert np.allclose(r4.velocity.data, [0, 0])
    assert np.allclose(r3.state.data, [0, 0, 0, 1, 1])
    assert np.allclose(r4.state.data, [1, 2, 0, 0])

    # Velocity operations.
    r3.velocity -= Velocity([2, 2])
    r4.velocity = r4.velocity + Velocity([2, 2])
    assert np.allclose(r3.velocity.data, [-1, -1])
    assert np.allclose(r4.velocity.data, [2, 2])
    assert np.allclose(r3.state.data, [0, 0, 0, -1, -1])
    assert np.allclose(r4.state.data, [1, 2, 2, 2])

    r3.velocity *= 2
    r4.velocity = -5 * r4.velocity
    assert np.allclose(r3.velocity.data, [-2, -2])
    assert np.allclose(r4.velocity.data, [-10, -10])
    assert np.allclose(r3.state.data, [0, 0, 0, -2, -2])
    assert np.allclose(r4.state.data, [1, 2, -10, -10])


def test_derivative_computation(generate_robot2D_list):

    r1, r2, r3, r4 = generate_robot2D_list

    # We check for the actual derivative values only for r3 and r4 as they
    # have the custom kinematic model. The other models have already been
    # tested on the cpp side.
    der1 = r1.compute_state_derivative(Input([0, 0]))
    der2 = r2.compute_state_derivative(State([1, 1, 1, 1], []), Input([0, 0]))
    der3 = r3.compute_state_derivative(
        State([1, 0, 0], [-1, 0]), Input([2, 2, 2, -2, 2]))
    der4 = r4.compute_state_derivative(Input([-1, 1, -2, 2]))

    assert np.allclose(der1.data, [0, 0, 0])
    assert np.allclose(der2.data, [0, 0, 0, 0])
    assert np.allclose(der3.data, [9] * 5)
    assert np.allclose(der4.data, [3] * 4)

    # Making sure that the derivative computation cannot be called with
    # incorrect state/input dimensions, even with a custom kinematic model.
    with pytest.raises(ValueError):
        r1.compute_state_derivative(Input([1, 1, 1]))
    with pytest.raises(ValueError):
        r2.compute_state_derivative(State(3, 0), Input(2))
    with pytest.raises(ValueError):
        r3.compute_state_derivative(Input(3))
    with pytest.raises(ValueError):
        r4.compute_state_derivative(State([1, 1], [2, 2]), Input(5))
    with pytest.raises(ValueError):
        r4.compute_state_derivative(State([1, 1, 0], [2, 2]), Input(2))
