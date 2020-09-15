import numpy as np
import pytest

from morphac.constructs import Velocity


@pytest.fixture()
def generate_velocity_list():

    # List of velocities constructed in every single way.
    # This also tests initialization.
    v1 = Velocity(size=2)
    v2 = Velocity([1, 2, 3])
    v3 = Velocity((4, 3, 2, 1))
    v4 = Velocity(data=np.array([1, 1, 2, 3, 5], dtype=np.float))

    return v1, v2, v3, v4


def test_size(generate_velocity_list):

    v1, v2, v3, v4 = generate_velocity_list

    assert v1.size == 2
    assert v2.size == 3
    assert v3.size == 4
    assert v4.size == 5

    # Making sure that size is read only.
    with pytest.raises(AttributeError):
        v1.size = 3
    with pytest.raises(AttributeError):
        v2.size = 3


def test_data(generate_velocity_list):

    v1, v2, v3, v4 = generate_velocity_list

    # Test getting data.
    assert np.allclose(v1.data, [0, 0])
    assert np.allclose(v2.data, [1.0, 2.0, 3.0])
    assert np.allclose(v3.data, [4.0, 3.0, 2.0, 1.0])
    assert np.allclose(v4.data, [1.0, 1.0, 2.0, 3.0, 5.0])

    # Test setting data.
    v1.data = np.array([1, 1], dtype=np.int)
    v2.data = np.array([-2, 3, 3], dtype=np.float)
    v3.data = [5, -13, -1, 0]
    v4.data = (-4, -6, -2, -3, -9)

    assert np.allclose(v1.data, [1, 1])
    assert np.allclose(v2.data, [-2, 3, 3])
    assert np.allclose(v3.data, [5, -13, -1, 0])
    assert np.allclose(v4.data, [-4, -6, -2, -3, -9])

    # Test invalid setting.
    with pytest.raises(ValueError):
        v1.data = [1, 1, 1]
    with pytest.raises(ValueError):
        v2.data = [1, 1]


def test_getitem(generate_velocity_list):

    v1, v2, v3, v4 = generate_velocity_list

    for v in [v1, v2, v3, v4]:
        for i in range(v.size):
            assert v[i] == v.data[i]
            # Test negative indexing.
            assert v[-(v.size - i)] == v.data[i]

    # Test invalid getitem.
    with pytest.raises(IndexError):
        _ = v1[-3]
    with pytest.raises(IndexError):
        _ = v2[3]
    with pytest.raises(IndexError):
        _ = v3[-5]
    with pytest.raises(IndexError):
        _ = v4[7]


def test_setitem(generate_velocity_list):

    v1, v2, v3, v4 = generate_velocity_list
    v1[0] = 1
    v2[1] = 1
    v3[2] = 7
    v4[0], v4[-1] = -1, 8

    assert np.allclose(v1.data, [1, 0])
    assert np.allclose(v2.data, [1, 1, 3])
    assert np.allclose(v3.data, [4, 3, 7, 1])
    assert np.allclose(v4.data, [-1, 1, 2, 3, 8])

    # Test invalid setitem
    with pytest.raises(IndexError):
        v1[-3] = 0
    with pytest.raises(IndexError):
        v2[3] = 1
    with pytest.raises(IndexError):
        v3[-5] = 2
    with pytest.raises(IndexError):
        v4[7] = 3


def test_addition(generate_velocity_list):

    v1, v2, v3, v4 = generate_velocity_list

    v1 += Velocity(2)
    assert np.allclose(v1.data, [0, 0])

    res = v2 + Velocity(3)
    assert np.allclose(res.data, v2.data)

    res = v3 + Velocity([0, 1, 2, 3])
    assert np.allclose(res.data, [4, 4, 4, 4])

    res = v4 + Velocity([-1, -2, -3, -4, -5])
    assert np.allclose(res.data, [0, -1, -1, -1, 0])

    # Test invalid addition.
    with pytest.raises(ValueError):
        v1 += Velocity(3)
    with pytest.raises(ValueError):
        res = v2 + v3


def test_subtraction(generate_velocity_list):

    v1, v2, v3, v4 = generate_velocity_list

    v1 -= Velocity(2)
    assert np.allclose(v1.data, [0, 0])

    res = v2 - Velocity(3)
    assert np.allclose(res.data, v2.data)

    res = v3 - Velocity([3, 2, 1, 0])
    assert np.allclose(res.data, [1, 1, 1, 1])

    res = v4 - Velocity([5, -4, 3, -2, 1])
    assert np.allclose(res.data, [-4, 5, -1, 5, 4])

    # Test invalid addition.
    with pytest.raises(ValueError):
        v1 -= Velocity(3)
    with pytest.raises(ValueError):
        res = v2 - v3


def test_multiplication(generate_velocity_list):

    v1, v2, v3, v4 = generate_velocity_list

    v1 *= 0
    assert np.allclose(v1.data, [0, 0])

    res = v2 * 0
    assert np.allclose(res.data, [0, 0, 0])

    res = v3 * 3
    assert np.allclose(res.data, [12, 9, 6, 3])

    res = v4 * (-2)
    assert np.allclose(res.data, [-2, -2, -4, -6, -10])

    # Test commutative property.
    assert np.allclose((v4 * (-2)).data, ((-2) * v4).data)


def test_equality(generate_velocity_list):

    v1, v2, v3, v4 = generate_velocity_list

    assert v1 == Velocity([0, 0])
    assert v2 == Velocity([1, 2, 3])
    assert v1 != v2


def test_repr(generate_velocity_list):

    for v in generate_velocity_list:
        assert isinstance(repr(v), str)


def test_empty():

    assert not Velocity(3).is_empty()
    assert Velocity(0).is_empty()


def test_create_like(generate_velocity_list):

    for v in generate_velocity_list:

        assert Velocity.create_like(velocity=v).size == v.size
        assert np.allclose(Velocity.create_like(v).data, np.zeros(v.size))
