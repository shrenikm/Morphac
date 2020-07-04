import numpy as np
import pytest

from morphac.constructs import State
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


def test_add_robot(generate_playground_state_list, generate_robot_list):
    ps1, _ = generate_playground_state_list
    r1, r2 = generate_robot_list

    # Adding the robots.
    ps1.add_robot(r1, 0)

    # Make sure that the robot has been added.
    assert ps1.num_robots == 1

    # Adding another robot and testing.
    ps1.add_robot(r2, 1)

    assert ps1.num_robots == 2

    # Test addition of robots with invalid or duplicate uids.
    with pytest.raises(ValueError):
        ps1.add_robot(r1, -1)
    with pytest.raises(ValueError):
        ps1.add_robot(r2, 0)
    with pytest.raises(ValueError):
        ps1.add_robot(r2, 1)


def test_robot_oracle(generate_playground_state_list, generate_robot_list):
    ps1, _ = generate_playground_state_list
    r1, r2 = generate_robot_list

    # Adding both robots.
    ps1.add_robot(r1, 1)
    ps1.add_robot(r2, 2)

    robot_oracle = ps1.robot_oracle

    # Making sure that its a dict and has the UIDs as keys.
    assert isinstance(robot_oracle, dict)
    assert 1 in robot_oracle
    assert 2 in robot_oracle

    # Checking the size.
    assert len(robot_oracle) == 2

    # Test that the correct robots are stored agains the UIDs.
    assert np.allclose(robot_oracle[1].state.data, [0, 0, 0])
    assert np.allclose(robot_oracle[2].state.data, [1, 2, 3])


def test_get_robot(generate_playground_state_list, generate_robot_list):
    ps1, _ = generate_playground_state_list
    r1, r2 = generate_robot_list

    # Adding both robots.
    ps1.add_robot(r1, 1)
    ps1.add_robot(r2, 2)

    # Test that the correct robots can be retrieved.
    assert np.allclose(ps1.get_robot(1).state.data, [0, 0, 0])
    assert np.allclose(ps1.get_robot(2).state.data, [1, 2, 3])

    # Trying to get a robot against an invalid uid must throw an exception.
    with pytest.raises(ValueError):
        ps1.get_robot(-1)
    with pytest.raises(ValueError):
        ps1.get_robot(3)


def test_get_robot_state(generate_playground_state_list, generate_robot_list):
    ps1, _ = generate_playground_state_list
    r1, r2 = generate_robot_list

    # Adding both robots.
    ps1.add_robot(r1, 1)
    ps1.add_robot(r2, 2)

    # Test that the correct robot states can be retrieved.
    assert np.allclose(ps1.get_robot_state(1).data, [0, 0, 0])
    assert np.allclose(ps1.get_robot_state(2).data, [1, 2, 3])

    # Trying to get a robot state against an invalid uid must throw an
    # exeption.
    with pytest.raises(ValueError):
        ps1.get_robot_state(-1)
    with pytest.raises(ValueError):
        ps1.get_robot_state(3)


def test_set_robot_state(generate_playground_state_list, generate_robot_list):
    ps1, _ = generate_playground_state_list
    r1, r2 = generate_robot_list

    # Adding both robots.
    ps1.add_robot(r1, 1)
    ps1.add_robot(r2, 2)

    # Setting different states.
    ps1.set_robot_state(State([-1, -2, -3], []), 1)
    ps1.set_robot_state(State([1, 1, 2], []), 2)

    # Make sure that the states have updated, through the oracle, robot and
    # robot states.
    robot_oracle = ps1.robot_oracle
    assert np.allclose(robot_oracle[1].state.data, [-1, -2, -3])
    assert np.allclose(robot_oracle[2].state.data, [1, 1, 2])
    assert np.allclose(ps1.get_robot(1).state.data, [-1, -2, -3])
    assert np.allclose(ps1.get_robot(2).state.data, [1, 1, 2])
    assert np.allclose(ps1.get_robot_state(1).data, [-1, -2, -3])
    assert np.allclose(ps1.get_robot_state(2).data, [1, 1, 2])

    # Trying to set a robot state against an invalid uid must throw an
    # exception.
    with pytest.raises(ValueError):
        ps1.set_robot_state(State(3, 0), -1)
    with pytest.raises(ValueError):
        ps1.set_robot_state(State(3, 0), 3)
