import numpy as np
import pytest

from morphac.constructs import ControlInput, State
from morphac.mechanics.models import KinematicModel
from morphac.robot.blueprint import Footprint

# Class that extends from KinematicModel. Testing if a functional subclass of
# the pybind binding of KinematicModel can be built.


class CustomKinematicModel(KinematicModel):
    def __init__(self, sp, sv, si, a, b):

        KinematicModel.__init__(self, sp, sv, si)
        self.a = a
        self.b = b

    def compute_state_derivative(self, robot_state, control_input):

        tmp_der = np.sum(np.multiply(robot_state.data, control_input.data))
        tmp_der = tmp_der + self.a * self.b
        # tmp_der is a scalar, but the derivative must be a State object.
        # Copying tmp_der to each State element.
        der = State([tmp_der] * self.pose_size, [tmp_der] * self.velocity_size)
        return der

    def default_footprint(self):

        return Footprint(np.ones([10, 2], dtype=np.float))


@pytest.fixture()
def generate_custom_model_list():

    c1 = CustomKinematicModel(3, 2, 5, 1.5, 2.3)
    c2 = CustomKinematicModel(1, 1, 2, 0.0, 0.0)
    c3 = CustomKinematicModel(2, 4, 6, -1.0, -10.0)

    return c1, c2, c3


def test_size(generate_custom_model_list):

    c1, c2, c3 = generate_custom_model_list

    assert c1.pose_size == 3
    assert c2.pose_size == 1
    assert c3.pose_size == 2

    assert c1.velocity_size == 2
    assert c2.velocity_size == 1
    assert c3.velocity_size == 4

    assert c1.control_input_size == 5
    assert c2.control_input_size == 2
    assert c3.control_input_size == 6

    # Making sure that the sizes are read only.
    with pytest.raises(AttributeError):
        c1.pose_size = 2
    with pytest.raises(AttributeError):
        c2.velocity_size = 1
    with pytest.raises(AttributeError):
        c3.control_input_size = 2


def test_members(generate_custom_model_list):

    c1, c2, c3 = generate_custom_model_list

    assert c1.a == 1.5
    assert c2.a == 0.0
    assert c3.a == -1.0

    assert c1.b == 2.3
    assert c2.b == 0.0
    assert c3.b == -10.0


def test_derivative_computation(generate_custom_model_list):

    c1, c2, c3 = generate_custom_model_list

    der1 = c1.compute_state_derivative(
        State([1, 1, 1], [1, 1]), ControlInput([1, 2, 3, 4, 5])
    )
    der2 = c2.compute_state_derivative(State([1], [0]), ControlInput([-2, -1]))

    # Test with positional arguments.
    der3 = c3.compute_state_derivative(
        robot_state=State([1, -1], [-0.1, 7, 9.5, 0]),
        control_input=ControlInput([5, 0, -100, -5, 4, 0]),
    )

    assert np.allclose(der1.data, [15.0 + 3.45] * 5)
    assert np.allclose(der2.data, [-2] * 2)
    assert np.allclose(der3.data, [18 + 10] * 6)


def test_normalize_state(generate_custom_model_list):

    c1, c2, c3 = generate_custom_model_list

    # Making sure that the default implementation of normalize_state returns
    # the given state without any changes.
    state1 = State([1.0, -2.0, 0.0], [1.0, 1.0])
    state2 = State(1, 1)
    state3 = State([1, 2], [3, 4, 5, 6])

    assert c1.normalize_state(state1) == state1
    assert c2.normalize_state(state2) == state2
    assert c3.normalize_state(robot_state=state3) == state3


def test_default_footprint(generate_custom_model_list):

    c1, _, _ = generate_custom_model_list

    footprint = c1.default_footprint()

    # Just making sure that the default_footprint function computes the right footprint.
    assert isinstance(footprint, Footprint)
    assert np.allclose(footprint.data, np.ones([10, 2]))