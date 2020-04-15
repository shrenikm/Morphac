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
    r2 = Robot2D("r2", TricycleModel("t", 1, 1),
                 Footprint2D(np.ones([20, 2])))
    r3 = Robot2D("r3", NewKinematicModel("k1", 2, 2, 2, 2.5, 2),
                 Footprint2D([[1, 0], [0, 1]]))
    r4 = Robot2D(name="r4",
                 kinematic_model=NewKinematicModel("k2", 2, 2, 4, 0, 0),
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

    assert isinstance(r1.kinematic_model, DiffDriveModel)
    assert isinstance(r2.kinematic_model, TricycleModel)
    assert isinstance(r3.kinematic_model, NewKinematicModel)
    assert isinstance(r4.kinematic_model, NewKinematicModel)
