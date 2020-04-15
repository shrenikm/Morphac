import numpy as np
import pytest

from morphac.constructs import Pose


@pytest.fixture()
def generate_pose_list():

    # List of poses constructed in every single way.
    # This also tests initialization.
    p1 = Pose(size=2)
    p2 = Pose([1, 2, 3])
    p3 = Pose((4, 3, 2, 1))
    p4 = Pose(data=np.array([1, 1, 2, 3, 5], dtype=np.float))

    return p1, p2, p3, p4


def test_size(generate_pose_list):

    p1, p2, p3, p4 = generate_pose_list

    assert p1.size == 2
    assert p2.size == 3
    assert p3.size == 4
    assert p4.size == 5

    # Making sure that size is read only.
    with pytest.raises(AttributeError):
        p1.size = 3
    with pytest.raises(AttributeError):
        p2.size = 3


def test_data(generate_pose_list):

    p1, p2, p3, p4 = generate_pose_list

    # Test getting data.
    assert np.allclose(p1.data, [0, 0])
    assert np.allclose(p2.data, [1., 2., 3.])
    assert np.allclose(p3.data, [4., 3., 2., 1.])
    assert np.allclose(p4.data, [1., 1., 2., 3., 5.])

    # Test setting data.
    p1.data = np.array([1, 1], dtype=np.int)
    p2.data = np.array([-2, 3, 3], dtype=np.float)
    p3.data = [5, -13, -1, 0]
    p4.data = (-4, -6, -2, -3, -9)

    assert np.allclose(p1.data, [1, 1])
    assert np.allclose(p2.data, [-2, 3, 3])
    assert np.allclose(p3.data, [5, -13, -1, 0])
    assert np.allclose(p4.data, [-4, -6, -2, -3, -9])

    # Test invalid setting.
    with pytest.raises(ValueError):
        p1.data = [1, 1, 1]
    with pytest.raises(ValueError):
        p2.data = [1, 1]


def test_addition(generate_pose_list):

    p1, p2, p3, p4 = generate_pose_list

    p1 += Pose(2)
    assert np.allclose(p1.data, [0, 0])

    res = p2 + Pose(3)
    assert np.allclose(res.data, p2.data)

    res = p3 + Pose([0, 1, 2, 3])
    assert np.allclose(res.data, [4, 4, 4, 4])

    res = p4 + Pose([-1, -2, -3, -4, -5])
    assert np.allclose(res.data, [0, -1, -1, -1, 0])

    # Test invalid addition.
    with pytest.raises(ValueError):
        p1 += Pose(3)
    with pytest.raises(ValueError):
        res = p2 + p3


def test_subtraction(generate_pose_list):

    p1, p2, p3, p4 = generate_pose_list

    p1 -= Pose(2)
    assert np.allclose(p1.data, [0, 0])

    res = p2 - Pose(3)
    assert np.allclose(res.data, p2.data)

    res = p3 - Pose([3, 2, 1, 0])
    assert np.allclose(res.data, [1, 1, 1, 1])

    res = p4 - Pose([5, -4, 3, -2, 1])
    assert np.allclose(res.data, [-4, 5, -1, 5, 4])

    # Test invalid addition.
    with pytest.raises(ValueError):
        p1 -= Pose(3)
    with pytest.raises(ValueError):
        res = p2 - p3


def test_multiplication(generate_pose_list):

    p1, p2, p3, p4 = generate_pose_list

    p1 *= 0
    assert np.allclose(p1.data, [0, 0])

    res = p2 * 0
    assert np.allclose(res.data, [0, 0, 0])

    res = p3 * 3
    assert np.allclose(res.data, [12, 9, 6, 3])

    res = p4 * (-2)
    assert np.allclose(res.data, [-2, -2, -4, -6, -10])

    # Test commutative property.
    assert np.allclose((p4 * (-2)).data, ((-2) * p4).data)


def test_repr(generate_pose_list):

    for p in generate_pose_list:
        assert isinstance(repr(p), str)


def test_empty():

    assert not Pose(3).is_empty()
    assert Pose(0).is_empty()


def test_create_like(generate_pose_list):

    for p in generate_pose_list:

        assert Pose.create_like(p).size == p.size
        assert np.allclose(Pose.create_like(p).data, np.zeros(p.size))
