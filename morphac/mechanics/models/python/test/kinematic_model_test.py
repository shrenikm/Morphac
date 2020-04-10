import numpy as np
import pytest

from morphac.mechanics.models import KinematicModel

# Class that extends from KinematicModel


class NewKinematicModel(KinematicModel):

    def __init__(self, name, sp, sv, si, a, b):

        KinematicModel.__init__(self, name, sp, sv, si)
        self.a = a
        self.b = b

    def compute_state_derivative(self, robot_state, robot_input):

        return np.sum(np.multiply(robot_state.data, robot_input.data))


@pytest.fixture()
def generate_kinematic_model_list():

    k1 = NewKinematicModel("k1", 3, 2, 5, 1.5, 2.3)
    k2 = NewKinematicModel("k2", 1, 1, 2, 0., 0.)
    k3 = NewKinematicModel("k3", 2, 4, 6, -1., -10.)

    return k1, k2, k3


def test_name(generate_kinematic_model_list):

    k1, k2, k3 = generate_kinematic_model_list

    assert k1.name == 'k1'
    assert k2.name == 'k2'
    assert k3.name == 'k3'


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


def test_members(generate_kinematic_model_list):

    k1, k2, k3 = generate_kinematic_model_list

    assert k1.a == 1.5
    assert k2.a == 0.
    assert k3.a == -1.

    assert k1.b == 2.3
    assert k2.b == 0.
    assert k3.b == -10.
