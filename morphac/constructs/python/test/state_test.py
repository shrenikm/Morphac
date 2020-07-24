import numpy as np
import pytest

from morphac.constructs import Pose, State, Velocity


@pytest.fixture()
def generate_state_list():

    # List of full states constructed in all the different ways.
    # Also tests initialization.

    # Full states.
    sf1 = State(pose_size=2, velocity_size=2)
    sf2 = State([1, 2], [3, 4])
    sf3 = State((5, 6), (7, 8, 9))
    sf4 = State(data_pose=np.array([1, 1, 2]), data_velocity=np.array(
        [3, 5, 8, 13], dtype=np.float))
    sf5 = State(pose=Pose([0, -1]), velocity=Velocity([-3, -7, 9]))

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

    # Making sure that size is read only.
    with pytest.raises(AttributeError):
        sf1.size = 2
    with pytest.raises(AttributeError):
        sf2.size = 4
    with pytest.raises(AttributeError):
        sp1.size = 4
    with pytest.raises(AttributeError):
        sp2.size = 3


def test_pose_size(generate_state_list):

    sf1, sf2, sf3, sf4, sf5, sp1, sp2 = generate_state_list

    assert sf1.pose_size == 2
    assert sf2.pose_size == 2
    assert sf3.pose_size == 2
    assert sf4.pose_size == 3
    assert sf5.pose_size == 2

    # Partial state pose_size.
    assert sp1.pose_size == 0
    assert sp2.pose_size == 3


def test_velocity_size(generate_state_list):

    sf1, sf2, sf3, sf4, sf5, sp1, sp2 = generate_state_list

    assert sf1.velocity_size == 2
    assert sf2.velocity_size == 2
    assert sf3.velocity_size == 3
    assert sf4.velocity_size == 4
    assert sf5.velocity_size == 3

    # Partial state pose_size.
    assert sp1.velocity_size == 2
    assert sp2.velocity_size == 0


def test_state_pose(generate_state_list):

    sf1, sf2, sf3, sf4, sf5, sp1, sp2 = generate_state_list

    # Full state pose.
    assert sf1.pose_size == 2
    assert np.allclose(sf1.pose.data, [0, 0])
    assert sf2.pose_size == 2
    assert np.allclose(sf2.pose.data, [1, 2])
    assert sf3.pose_size == 2
    assert np.allclose(sf3.pose.data, [5, 6])
    assert sf4.pose_size == 3
    assert np.allclose(sf4.pose.data, [1, 1, 2])
    assert sf5.pose_size == 2
    assert np.allclose(sf5.pose.data, [0, -1])

    # Partial state pose.
    # Shouldn't be able to access the pose of a state whose pose is empty.
    with pytest.raises(RuntimeError):
        sp1.pose
    assert sp2.pose_size == 3
    assert np.allclose(sp2.pose.data, [4, 6, 5.9])

    # Testing setting pose data.
    # Doesn't have to be tested too much as the Pose tests cover it.
    # Only need to test if the changes are reflected in the State object.
    sf1.pose.data = [1, 1]
    sp2.pose.data = (1, -1, 1)

    assert np.allclose(sf1.data, [1, 1, 0, 0])
    assert np.allclose(sp2.data, [1, -1, 1])

    # Full state pose set.
    sf1.pose = Pose([1, 2])
    sf4.pose = Pose([0, 1, 0])

    assert np.allclose(sf1.pose.data, [1, 2])
    assert np.allclose(sf1.data, [1, 2, 0, 0])
    assert np.allclose(sf4.pose.data, [0, 1, 0])
    assert np.allclose(sf4.data, [0, 1, 0, 3, 5, 8, 13])

    # Partial state pose set.
    sp2.pose = Pose(3)
    assert np.allclose(sp2.pose.data, [0, 0, 0])
    assert np.allclose(sp2.data, [0, 0, 0])

    # Invalid pose set.
    with pytest.raises(ValueError):
        sf1.pose = Pose(1)
    with pytest.raises(ValueError):
        sf4.pose = Pose([1, 2])
    with pytest.raises(ValueError):
        sp1.pose = Pose(1)
    with pytest.raises(ValueError):
        sp2.pose = Pose([0, 0, 0, 0])


def test_state_velocity(generate_state_list):

    sf1, sf2, sf3, sf4, sf5, sp1, sp2 = generate_state_list

    # Full state velocity.
    assert sf1.velocity_size == 2
    assert np.allclose(sf1.velocity.data, [0, 0])
    assert sf2.velocity_size == 2
    assert np.allclose(sf2.velocity.data, [3, 4])
    assert sf3.velocity_size == 3
    assert np.allclose(sf3.velocity.data, [7, 8, 9])
    assert sf4.velocity_size == 4
    assert np.allclose(sf4.velocity.data, [3, 5, 8, 13])
    assert sf5.velocity_size == 3
    assert np.allclose(sf5.velocity.data, [-3, -7, 9])

    # Partial state velocity.
    assert sp1.velocity_size == 2
    assert np.allclose(sp1.velocity.data, [0, 0])
    # Shouldn't be able to access the pose of a state whose pose is empty.
    with pytest.raises(RuntimeError):
        sp2.velocity

    # Testing setting velocitiy data.
    # Doesn't have to be tested too much as the Velocity tests cover it.
    # Only need to test if the changes are reflected in the State object.
    sf1.velocity.data = [1, 1]
    sp1.velocity.data = (1, -1)

    assert np.allclose(sf1.data, [0, 0, 1, 1])
    assert np.allclose(sp1.data, [1, -1])

    # Full state pose set.
    sf1.velocity = Velocity([1, 2])
    sf4.velocity = Velocity([0, 1, 0, 1])

    assert np.allclose(sf1.velocity.data, [1, 2])
    assert np.allclose(sf1.data, [0, 0, 1, 2])
    assert np.allclose(sf4.velocity.data, [0, 1, 0, 1])
    assert np.allclose(sf4.data, [1, 1, 2, 0, 1, 0, 1])

    # Partial state pose set.
    sp1.velocity = Velocity(2)
    assert np.allclose(sp1.velocity.data, [0, 0])
    assert np.allclose(sp1.data, [0, 0])

    # Invalid pose set.
    with pytest.raises(ValueError):
        sf1.velocity = Velocity(1)
    with pytest.raises(ValueError):
        sf4.velocity = Velocity([1, 2, 3])
    with pytest.raises(ValueError):
        sp1.velocity = Velocity([0, 0, 0])
    with pytest.raises(ValueError):
        sp2.velocity = Velocity(1)


def test_data(generate_state_list):

    sf1, sf2, sf3, sf4, sf5, sp1, sp2 = generate_state_list

    # Test getting data.

    # Full state data.
    assert np.allclose(sf1.data, [0, 0, 0, 0])
    assert np.allclose(sf2.data, [1, 2, 3, 4])
    assert np.allclose(sf3.data, [5, 6, 7, 8, 9])
    assert np.allclose(sf4.data, [1, 1, 2, 3, 5, 8, 13])
    assert np.allclose(sf5.data, [0, -1, -3, -7, 9])

    # Partial state data.
    assert np.allclose(sp1.data, [0, 0])
    assert np.allclose(sp2.data, [4, 6, 5.9])

    # Test setting data.

    # Full state data.
    sf1.data = np.array([1, 1, 1, 1])
    sf2.data = np.array([0, 1, 0, -1], dtype=np.int)
    sf3.data = np.array([9, 8, 7, 6, 5], dtype=np.float)
    sf4.data = [0, 0, 0, -7, 0, 0, 0]
    sf5.data = (5, 5, 5, 5, 5)

    # Partial state data.
    sp1.data = [1, 1]
    sp2.data = (-1, 2, -3)

    assert np.allclose(sf1.data, [1, 1, 1, 1])
    assert np.allclose(sf2.data, [0, 1, 0, -1])
    assert np.allclose(sf3.data, [9, 8, 7, 6, 5])
    assert np.allclose(sf4.data, [0, 0, 0, -7, 0, 0, 0])
    assert np.allclose(sf5.data, [5, 5, 5, 5, 5])

    assert np.allclose(sp1.data, [1, 1])
    assert np.allclose(sp2.data, [-1, 2, -3])

    # Test invalid setting.
    with pytest.raises(ValueError):
        sf1.data = [1, 1, 1]
    with pytest.raises(ValueError):
        sf2.data = [1, 1, 1, 1, 1]
    with pytest.raises(ValueError):
        sp1.data = [1, 1, 1]
    with pytest.raises(ValueError):
        sp2.data = [1, 1]


def test_getitem(generate_state_list):

    sf1, sf2, sf3, sf4, sf5, sp1, sp2 = generate_state_list

    for s in [sf1, sf2, sf3, sf4, sf5, sp1, sp2]:
        for i in range(s.size):
            assert s[i] == s.data[i]

    # Test invalid getitem.
    with pytest.raises(IndexError):
        _ = sf1[-1]
    with pytest.raises(IndexError):
        _ = sf2[4]
    with pytest.raises(IndexError):
        _ = sp1[-1]
    with pytest.raises(IndexError):
        _ = sp2[3]


def test_setitem(generate_state_list):

    sf1, sf2, sf3, sf4, sf5, sp1, sp2 = generate_state_list

    sf1[0] = 1
    sf2[1] = -2
    sf3[2] = 3
    sf4[0], sf4[6] = -1, 9
    sf5[0], sf5[2], sf5[4] = -3, 9, 0
    sp1[0] = 1
    sp2[1], sp2[2] = 5.9, 6

    # Make sure that the full states are updated correctly.
    assert np.allclose(sf1.data, [1, 0, 0, 0])
    assert np.allclose(sf2.data, [1, -2, 3, 4])
    assert np.allclose(sf3.data, [5, 6, 3, 8, 9])
    assert np.allclose(sf4.data, [-1, 1, 2, 3, 5, 8, 9])
    assert np.allclose(sf5.data, [-3, -1, 9, -7, 0])

    # Make sure that the partial states are updated correctly.
    assert np.allclose(sp1.data, [1, 0])
    assert np.allclose(sp2.data, [4, 5.9, 6])

    # Test invalid setitem
    with pytest.raises(IndexError):
        sf1[-1] = 0
    with pytest.raises(IndexError):
        sf2[4] = 1
    with pytest.raises(IndexError):
        sp1[-1] = 2
    with pytest.raises(IndexError):
        sp2[3] = 3


def test_addition(generate_state_list):

    sf1, sf2, sf3, sf4, sf5, sp1, sp2 = generate_state_list

    # Full state addition.
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

    # Partial state addition.
    sp1 += State(0, 2)
    assert np.allclose(sp1.data, [0, 0])

    res = sp2 + State([-5, -1, 0.1], [])
    assert np.allclose(res.data, [-1, 5, 6])

    # Test invalid addition.
    with pytest.raises(ValueError):
        sf1 += State(2, 3)
    with pytest.raises(ValueError):
        res = sf1 + State(3, 2)
    with pytest.raises(ValueError):
        sp1 += State(2, 2)
    with pytest.raises(ValueError):
        res = sp2 + State(0, 3)


def test_subtraction(generate_state_list):

    sf1, sf2, sf3, sf4, sf5, sp1, sp2 = generate_state_list

    # Full state subtraction.
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

    # Partial state subtraction.
    sp1 -= State(0, 2)
    assert np.allclose(sp1.data, [0, 0])

    res = sp2 - State([6, 6, 0.9], [])
    assert np.allclose(res.data, [-2, 0, 5])

    # Test invalid Subtraction.
    with pytest.raises(ValueError):
        sf1 -= State(2, 3)
    with pytest.raises(ValueError):
        res = sf1 - State(3, 2)
    with pytest.raises(ValueError):
        sp1 -= State(2, 2)
    with pytest.raises(ValueError):
        res = sp2 - State(0, 3)


def test_multiplication(generate_state_list):

    sf1, sf2, sf3, sf4, sf5, sp1, sp2 = generate_state_list

    # Full state multiplication.
    sf1 *= 0
    assert np.allclose(sf1.data, [0, 0, 0, 0])

    res = sf2 * 0
    assert np.allclose(res.data, [0, 0, 0, 0])

    res = sf3 * 2
    assert np.allclose(res.data, [10, 12, 14, 16, 18])

    res = sf4 * (3)
    assert np.allclose(res.data, [3, 3, 6, 9, 15, 24, 39])

    res = sf5 * (-2)
    assert np.allclose(res.data, [0, 2, 6, 14, -18])

    # Commutative property.
    assert np.allclose((sf5 * (-2)).data, ((-2) * sf5).data)

    # Partial state multiplication.
    res = sp1 * 2
    assert np.allclose(res.data, [0, 0])

    res = sp2 * (-1)
    assert np.allclose(res.data, [-4, -6, -5.9])


def test_equality(generate_state_list):

    sf1, sf2, _, _, _, sp1, sp2 = generate_state_list

    assert sf1 == State([0, 0], [0, 0])
    assert sf2 == State([1, 2], [3, 4])
    assert sf1 != sf2

    # Partial state equality.
    assert sp1 == State([], [0, 0])
    assert sp2 == State([4, 6, 5.9], [])
    assert sp1 != sp2


def test_repr(generate_state_list):

    for s in generate_state_list:
        assert isinstance(repr(s), str)


def test_empty():

    assert not State(3, 3).is_empty()
    assert not State(3, 3).is_pose_empty()
    assert not State(3, 3).is_velocity_empty()

    assert not State(2, 0).is_empty()
    assert not State(2, 0).is_pose_empty()
    assert State(2, 0).is_velocity_empty()

    assert not State(0, 4).is_empty()
    assert State(0, 4).is_pose_empty()
    assert not State(0, 4).is_velocity_empty()

    assert State(0, 0).is_empty()
    assert State(0, 0).is_pose_empty()
    assert State(0, 0).is_velocity_empty()


def test_create_like(generate_state_list):

    for s in generate_state_list:

        zero_state = State.create_like(s)
        assert zero_state.size == s.size
        # Make sure that if partial, they are of the same configuration.
        assert zero_state.is_empty() == s.is_empty()
        assert zero_state.is_pose_empty() == s.is_pose_empty()
        assert zero_state.is_velocity_empty() == s.is_velocity_empty()
        assert np.allclose(State.create_like(s).data, np.zeros(s.size))
