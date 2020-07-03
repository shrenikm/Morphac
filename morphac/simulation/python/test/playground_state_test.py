import numpy as np
import pytest

from morphac.environment import Map
from morphac.mechanics.models import DiffDriveModel
from morphac.robot.blueprint import Footprint, Robot
from morphac.simulation import PlaygroundState


@pytest.fixture()
def generate_playground_state_list():
    ps1 = PlaygroundState(Map(10., 10., 0.1))
    ps2 = PlaygroundState(map=Map(np.ones([200, 200], dtype=np.float), 0.1))

    return ps1, ps2


@pytest.fixture()
def generate_robot_list():
    r1 = Robot(DiffDriveModel(1., 1.), Footprint([[0, 0]]))
    r2 = Robot(DiffDriveModel(2., 3.), Footprint(
        [[0, 0]]), State([1., 2., 3.], []))

    return r1, r2


def test_map(generate_playground_state_list):
    ps1, ps2 = generate_playground_state_list

    # Test map retrieval.
    assert ps1.map.width == 10.
    assert ps1.map.height == 10.
    assert ps1.map.resolution == 0.1
    assert np.all(ps1.map.data == 0.)

    assert ps2.map.width == 20.
    assert ps2.map.height == 20.
    assert ps2.map.resolution == 0.1
    assert np.all(ps2.map.data == 1.)

    # Test map setting.
    ps1.map = Map(10., 10., 0.5)
    ps2.map = Map(20., 20., 0.8)

    assert ps1.map.resolution == 0.5
    assert ps2.map.resolution == 0.8
    assert np.all(ps2.map.data == 0.)
