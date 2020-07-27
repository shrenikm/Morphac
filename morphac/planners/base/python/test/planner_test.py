import numpy as np
import pytest

from morphac.constructs import Trajectory
from morphac.planners.base import Planner


class CustomPlanner(Planner):
    def __init__(self, trajectory_data, pose_size, velocity_size):

        Planner.__init__(self)
        self.trajectory_data = trajectory_data
        self.pose_size = pose_size
        self.velocity_size = velocity_size

    def compute(self):

        return Trajectory(
            self.trajectory_data, self.pose_size, self.velocity_size)


@pytest.fixture()
def generate_planner_list():
    np.random.seed(7)
    p1 = CustomPlanner(np.random.randn(1, 3), 2, 1)
    p2 = CustomPlanner(np.random.randn(20, 5), 2, 3)

    return p1, p2


def test_compute(generate_planner_list):

    p1, p2 = generate_planner_list

    np.random.seed(7)
    data1 = np.random.randn(1, 3)
    data2 = np.random.randn(20, 5)

    assert np.allclose(p1.compute().data, data1)
    assert np.allclose(p2.compute().data, data2)
