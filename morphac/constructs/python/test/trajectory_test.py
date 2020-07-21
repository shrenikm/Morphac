import numpy as np
import pytest

from morphac.constructs import State, Trajectory


@pytest.fixture()
def generate_trajectory_list():
    # List of trajectories constructed in different ways.
    t1 = Trajectory(knot_point=State(2, 2))
    t2 = Trajectory(
        knot_points=[State([1, 1], [1]),
                     State([2, 2], [2]),
                     State([3, 3], [3])])
    np.random.seed(7)
    t3 = Trajectory(data=np.random.randn(100, 5), pose_size=3, velocity_size=2)

    return t1, t2, t3


def test_dim(generate_trajectory_list):

    t1, t2, t3 = generate_trajectory_list

    assert t1.dim == 4
    assert t2.dim == 3
    assert t3.dim == 5

    # Making sure that the dim is read only.
    with pytest.raises(AttributeError):
        t1.dim = 3
    with pytest.raises(AttributeError):
        t2.dim = 2
    with pytest.raises(AttributeError):
        t3.dim = 5
