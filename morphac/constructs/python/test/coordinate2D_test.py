import numpy as np
import pytest

from morphac.constructs import Coordinate2D


@pytest.fixture()
def generate_coord_list():

    # List of coordinates constructed in every single way.
    # This is also an initialization test.
    c1 = Coordinate2D(0, 0)
    c2 = Coordinate2D(1.5, 2.)
    c3 = Coordinate2D(x=1.5, y=-5.)
    c4 = Coordinate2D(x=-9., y=-1.2)

    return c1, c2, c3, c4


def test_xy(generate_coord_list):

    c1, c2, c3, c4 = generate_coord_list

    # Test getting.
    assert c1.x == 0
    assert c1.y == 0
    assert np.allclose(c1.data, [0, 0])
    assert c2.x == 1.5
    assert c2.y == 2
    assert np.allclose(c2.data, [1.5, 2])
    assert c3.x == 1.5
    assert c3.y == -5
    assert np.allclose(c3.data, [1.5, -5])
    assert c4.x == -9
    assert c4.y == -1.2
    assert np.allclose(c4.data, [-9, -1.2])

    # Test setting.
    c1.x = 1
    c1.y = -1
    assert c1.x == 1
    assert c1.y == -1
    assert np.allclose(c1.data, [1, -1])


def test_getitem(generate_coord_list):

    c1, c2, c3, c4 = generate_coord_list

    assert c1[0] == 0
    assert c1[1] == 0
    assert c2[0] == 1.5
    assert c2[1] == 2.
    assert c3[0] == 1.5
    assert c3[1] == -5.
    assert c4[0] == -9.
    assert c4[1] == -1.2


def test_invalid_getitem(generate_coord_list):

    c1, c2, _, _ = generate_coord_list

    with pytest.raises(IndexError):
        _ = c1[-1]
    with pytest.raises(IndexError):
        _ = c2[2]


def test_setitem(generate_coord_list):

    c1, c2, c3, c4 = generate_coord_list

    c1[0], c1[1] = 1, 1
    c2[0], c2[1] = 2, 2
    c3[0], c3[1] = 3, 3
    c4[0], c4[1] = 4, 4

    assert c1[0] == 1
    assert c1[1] == 1
    assert c2[0] == 2
    assert c2[1] == 2
    assert c3[0] == 3
    assert c3[1] == 3
    assert c4[0] == 4
    assert c4[1] == 4


def test_invalid_setitem(generate_coord_list):

    c1, c2, _, _ = generate_coord_list

    with pytest.raises(IndexError):
        c1[-1] = 0
    with pytest.raises(IndexError):
        c2[2] = 0


def test_addition(generate_coord_list):

    c1, c2, c3, c4 = generate_coord_list

    c1 += Coordinate2D(0, 0)
    assert np.allclose(c1.data, [0, 0])

    res = c2 + Coordinate2D(0, 0)
    assert np.allclose(res.data, c2.data)

    res = c3 + Coordinate2D(-1.5, 5.)
    assert np.allclose(res.data, [0, 0])

    res = c4 + Coordinate2D(-1, 5)
    assert np.allclose(res.data, [-10, 3.8])


def test_subtraction(generate_coord_list):

    c1, c2, c3, c4 = generate_coord_list

    c1 -= Coordinate2D(0, 0)
    assert np.allclose(c1.data, [0, 0])

    res = c2 - Coordinate2D(0, 0)
    assert np.allclose(res.data, c2.data)

    res = c3 - Coordinate2D(1.5, -5)
    assert np.allclose(res.data, [0, 0])

    res = c4 - Coordinate2D(1, -5)
    assert np.allclose(res.data, [-10, 3.8])


def test_multiplication(generate_coord_list):

    c1, c2, c3, c4 = generate_coord_list

    c1 *= 0
    assert np.allclose(c1.data, [0, 0])

    res = c2 * 0
    assert np.allclose(res.data, [0, 0])

    res = c3 * 2
    assert np.allclose(res.data, [3, -10])

    res = c4 * (-3)
    assert np.allclose(res.data, [27, 3.6])

    # Test commutative property.
    assert np.allclose((c4 * (-2)).data, ((-2) * c4).data)


def test_repr(generate_coord_list):

    for c in generate_coord_list:
        assert isinstance(repr(c), str)
