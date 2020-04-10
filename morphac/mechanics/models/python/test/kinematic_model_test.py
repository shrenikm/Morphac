import numpy as np
import pytest

from morphac.constructs import State, ControlInput
from morphac.mechanics.models import KinematicModel

# Class that extends from KinematicModel


class NewKinematicModel(KinematicModel):

    def __init__(self, name, sp, sv, si, a, b):

        KinematicModel.__init__(self, name, sp, sv, si)
        self.a = a
        self.b = b

    def compute_state_derivative(self, robot_state, robot_input):

        tmp_der = np.sum(np.multiply(robot_state.data, robot_input.data))
        return tmp_der + self.a * self.b


@pytest.fixture()
def generate_kinematic_model_list():

    k1 = NewKinematicModel("k1", 3, 2, 5, 1.5, 2.3)
    k2 = NewKinematicModel("k2", 1, 1, 2, 0., 0.)
    k3 = NewKinematicModel("k3", 2, 4, 6, -1., -10.)

    return k1, k2, k3


def test_name(generate_kinematic_model_list):

    k1, k2, k3 = generate_kinematic_model_list

    assert k1.name == "k1"
    assert k2.name == "k2"
    assert k3.name == "k3"

    # Making sure that name is read only.
    with pytest.raises(AttributeError):
        k1.name = "k2"


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


def test_overload(generate_kinematic_model_list):

    k1, k2, k3 = generate_kinematic_model_list

    derivative1 = k1.compute_state_derivative(
        State([1, 1, 1], [1, 1]), ControlInput([1, 2, 3, 4, 5]))
    derivative2 = k2.compute_state_derivative(
        State([1], [0]), ControlInput([-2, -1]))
    derivative3 = k3.compute_state_derivative(
        State([1, -1], [-0.1, 7, 9.5]), ControlInput([5, 0, -100, -5, 4]))

    assert np.isclose(derivative1, 15. + 3.45)
    assert np.isclose(derivative2, -2)
    assert np.isclose(derivative3, 18 + 10)
