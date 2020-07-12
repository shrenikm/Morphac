import numpy as np
import pytest

from morphac.constructs import ControlInput
from morphac.planners import Planner


class CustomPlanner(Planner):
    def __init__(self, control_input_data):

        Planner.__init__(self)
        self.control_input_data = control_input_data

    def compute(self):

        return ControlInput(self.control_input_data)


@pytest.fixture()
def generate_planner_list():
    p1 = CustomPlanner([-1, 2, 3])
    p2 = CustomPlanner([7., 8., 9.])

    return p1, p2


def test_compute(generate_planner_list):

    p1, p2 = generate_planner_list

    assert np.allclose(p1.compute().data, [-1., 2., 3.])
    assert np.allclose(p2.compute().data, [7, 8, 9])
