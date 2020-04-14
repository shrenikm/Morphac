import numpy as np
import pytest

from morphac.constructs import State
from morphac.mechanics.models import (
    KinematicModel,
    DiffDriveModel,
    TricycleModel
)
from morphac.robot.blueprint import Footprint2D, Robot2D

# KinematicModel extension class to ensure that a robot can be created from
# a subclassed KinematicModel


class NewKinematicModel(KinematicModel):

    def __init__(self, name, sp, sv, si, a, b):

        KinematicModel.__init__(self, name, sp, sv, si)
        self.a = a
        self.b = b

    def compute_state_derivative(self, robot_state, robot_input):

        tmp_der = np.sum(np.multiply(robot_state.data, robot_input.data))
        return tmp_der + self.a * self.b


@pytest.fixture()
def generate_robot2D_list():

    r1 = Robot2D("r1", DiffDriveModel("d", 1, 1), Footprint2D([[1, 2]]))
    r2 = Robot2D("r2", TricycleModel("t", 1, 1), Footprint2D(np.ones([20, 2])))

    return r1, r2


def test_name(generate_robot2D_list):

    r1, r2 = generate_robot2D_list

    assert r1.name == "r1"
    assert r2.name == "r2"

    # Making sure that the name is read only.
    with pytest.raises(AttributeError):
        r1.name = "r2"
    with pytest.raises(AttributeError):
        r2.name = "r1"
