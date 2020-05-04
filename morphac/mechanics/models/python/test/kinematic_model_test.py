import numpy as np
import pytest

from morphac.constructs import Input, State
from morphac.mechanics.models import KinematicModel

# Class that extends from KinematicModel. Testing if a functional subclass of
# the pybind binding of KinematicModel can be built.


class CustomKinematicModel(KinematicModel):

    def __init__(self, sp, sv, si, a, b):

        KinematicModel.__init__(self, sp, sv, si)
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
def generate_kinematic_model_list():

    k1 = CustomKinematicModel(3, 2, 5, 1.5, 2.3)
    k2 = CustomKinematicModel(1, 1, 2, 0., 0.)
    k3 = CustomKinematicModel(2, 4, 6, -1., -10.)

    return k1, k2, k3


def test_size(generate_kinematic_model_list):

    k1, k2, k3 = generate_kinematic_model_list

    assert k1.size_pose == 3
    assert k2.size_pose == 1
    assert k3.size_pose == 2

    assert k1.size_velocity == 2
    assert k2.size_velocity == 1
    assert k3.size_velocity == 4

    assert k1.size_input == 5
    assert k2.size_input == 2
    assert k3.size_input == 6

    # Making sure that the sizes are read only.
    with pytest.raises(AttributeError):
        k1.size_pose = 2
    with pytest.raises(AttributeError):
        k2.size_velocity = 1
    with pytest.raises(AttributeError):
        k3.size_input = 2


def test_members(generate_kinematic_model_list):

    k1, k2, k3 = generate_kinematic_model_list

    assert k1.a == 1.5
    assert k2.a == 0.
    assert k3.a == -1.

    assert k1.b == 2.3
    assert k2.b == 0.
    assert k3.b == -10.


def test_derivative_computation(generate_kinematic_model_list):

    k1, k2, k3 = generate_kinematic_model_list

    der1 = k1.compute_state_derivative(
        State([1, 1, 1], [1, 1]), Input([1, 2, 3, 4, 5]))
    der2 = k2.compute_state_derivative(
        State([1], [0]), Input([-2, -1]))
    der3 = k3.compute_state_derivative(
        State([1, -1], [-0.1, 7, 9.5, 0]), Input([5, 0, -100, -5, 4, 0]))

    assert np.allclose(der1.data, [15. + 3.45] * 5)
    assert np.allclose(der2.data, [-2] * 2)
    assert np.allclose(der3.data, [18 + 10] * 6)


def test_normalize_state(generate_kinematic_model_list):

    k1, k2, k3 = generate_kinematic_model_list

    # Making sure that the default implementation of normalize_state returns
    # the given state without any changes.
    state1 = State([1., -2., 0.], [1., 1.])
    state2 = State(1, 1)
    state3 = State([1, 2], [3, 4, 5, 6])

    assert k1.normalize_state(state1) == state1
    assert k2.normalize_state(state2) == state2
    assert k3.normalize_state(state3) == state3
