import numpy as np
import pytest

from morphac.constructs import Pose, Velocity, State


@pytest.fixture()
def generate_state_list():

    # List of full states constructed in all the different ways.
    # Also tests initialization

    # Full states.
    sf1 = State(2, 2)
    sf2 = State([1, 2], [3, 4])
    sf3 = State((5, 6), (7, 8, 9))
    sf4 = State(np.array([1, 1, 2]), np.array([3, 5, 8, 13], dtype=np.float))
    sf5 = State(Pose([0, -1]), Velocity([-3, -7, 9]))

    # Partial states.
    sp1 = State(0, 2)
    sp2 = State([4, 6, 5.9], [])

    return sf1, sf2, sf3, sf4, sf5, sp1, sp2


def test_size(generate_state_list):

    sf1, sf2, sf3, sf4, sf5, sp1, sp2 = generate_state_list

    # Full state size.
    assert sf1.size == 4
    assert sf2.size == 4
    assert sf3.size == 5
    assert sf4.size == 7
    assert sf5.size == 5

    # Partial state size.
    assert sp1.size == 2
    assert sp2.size == 3


def test_state_pose(generate_state_list):

    sf1, sf2, sf3, sf4, sf5, sp1, sp2 = generate_state_list

    # Full state pose.
    assert sf1.pose.size == 2
    assert np.allclose(sf1.pose.data, [0, 0])
    assert sf2.pose.size == 2
    assert np.allclose(sf2.pose.data, [1, 2])
    assert sf3.pose.size == 2
    assert np.allclose(sf3.pose.data, [5, 6])
    assert sf4.pose.size == 3
    assert np.allclose(sf4.pose.data, [1, 1, 2])
    assert sf5.pose.size == 2
    assert np.allclose(sf5.pose.data, [0, -1])

    # Partial state pose.
    assert sp1.pose.size == 0
    assert sp2.pose.size == 3
    assert np.allclose(sp2.pose.data, [4, 6, 5.9])


def test_state_velocity(generate_state_list):

    sf1, sf2, sf3, sf4, sf5, sp1, sp2 = generate_state_list

    # Full state velocity.
    assert sf1.velocity.size == 2
    assert np.allclose(sf1.velocity.data, [0, 0])
    assert sf2.velocity.size == 2
    assert np.allclose(sf2.velocity.data, [3, 4])
    assert sf3.velocity.size == 3
    assert np.allclose(sf3.velocity.data, [7, 8, 9])
    assert sf4.velocity.size == 4
    assert np.allclose(sf4.velocity.data, [3, 5, 8, 13])
    assert sf5.velocity.size == 3
    assert np.allclose(sf5.velocity.data, [-3, -7, 9])

    # Partial state velocity.
    assert sp1.velocity.size == 2
    assert np.allclose(sp1.velocity.data, [0, 0])
    assert sp2.velocity.size == 0


def test_data(generate_state_list):

    sf1, sf2, sf3, sf4, sf5, sp1, sp2 = generate_state_list

    # Full state data.
    assert np.allclose(sf1.data, [0, 0, 0, 0])
    assert np.allclose(sf2.data, [1, 2, 3, 4])
    assert np.allclose(sf3.data, [5, 6, 7, 8, 9])
    assert np.allclose(sf4.data, [1, 1, 2, 3, 5, 8, 13])
    assert np.allclose(sf5.data, [0, -1, -3, -7, 9])

    # Partial state data.
    assert np.allclose(sp1.data, [0, 0])
    assert np.allclose(sp2.data, [4, 6, 5.9])


def test_addition(generate_state_list):

    sf1, sf2, sf3, sf4, sf5, sp1, sp2 = generate_state_list

    # Full state addition
    sf1 += State(2, 2)
    assert np.allclose(sf1.data, [0, 0, 0, 0])

    res = sf2 + State(2, 2)
    assert np.allclose(res.data, sf2.data)

    res = sf3 + State([4, 3], [2, 1, 0])
    assert np.allclose(res.data, [9, 9, 9, 9, 9])

    res = sf4 + State([-1, -1, -2], [-3, 0, 0, 0])
    assert np.allclose(res.data, [0, 0, 0, 0, 5, 8, 13])

    res = sf5 + State([-5, -4], [-2, 2, -14])
    assert np.allclose(res.data, [-5, -5, -5, -5, -5])

    # Partial state addition
    sp1 += State(0, 2)
    assert np.allclose(sp1.data, [0, 0])

    res = sp2 + State([-5, -1, 0.1], [])
    assert np.allclose(res.data, [-1, 5, 6])


def test_subtraction(generate_state_list):

    sf1, sf2, sf3, sf4, sf5, sp1, sp2 = generate_state_list

    # Full state subtraction
    sf1 -= State(2, 2)
    assert np.allclose(sf1.data, [0, 0, 0, 0])

    res = sf2 - State(2, 2)
    assert np.allclose(res.data, sf2.data)

    res = sf3 - State([0, 1], [2, 3, 4])
    assert np.allclose(res.data, [5, 5, 5, 5, 5])

    res = sf4 - State([1, 1, 2], [3, 0, 0, 0])
    assert np.allclose(res.data, [0, 0, 0, 0, 5, 8, 13])

    res = sf5 - State([9, 9], [9, 9, 9])
    assert np.allclose(res.data, [-9, -10, -12, -16, 0])

    # Partial state subtraction
    sp1 -= State(0, 2)
    assert np.allclose(sp1.data, [0, 0])

    res = sp2 - State([6, 6, 0.9], [])
    assert np.allclose(res.data, [-2, 0, 5])
