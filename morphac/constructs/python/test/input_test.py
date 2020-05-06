import numpy as np
import pytest

from morphac.constructs import Input


@pytest.fixture()
def generate_input_list():

    # List of velocities constructed in every single way.
    # This also tests initialization.
    ci1 = Input(size=2)
    ci2 = Input([1, 2, 3])
    ci3 = Input((4, 3, 2, 1))
    ci4 = Input(data=np.array([1, 1, 2, 3, 5], dtype=np.float))

    return ci1, ci2, ci3, ci4


def test_size(generate_input_list):

    ci1, ci2, ci3, ci4 = generate_input_list

    assert ci1.size == 2
    assert ci2.size == 3
    assert ci3.size == 4
    assert ci4.size == 5

    # Making sure that size is read only.
    with pytest.raises(AttributeError):
        ci1.size = 3
    with pytest.raises(AttributeError):
        ci2.size = 3


def test_data(generate_input_list):

    ci1, ci2, ci3, ci4 = generate_input_list

    # Test getting data.
    assert np.allclose(ci1.data, [0, 0])
    assert np.allclose(ci2.data, [1., 2., 3.])
    assert np.allclose(ci3.data, [4., 3., 2., 1.])
    assert np.allclose(ci4.data, [1., 1., 2., 3., 5.])

    # Test setting data.
    ci1.data = np.array([1, 1], dtype=np.int)
    ci2.data = np.array([-2, 3, 3], dtype=np.float)
    ci3.data = [5, -13, -1, 0]
    ci4.data = (-4, -6, -2, -3, -9)

    assert np.allclose(ci1.data, [1, 1])
    assert np.allclose(ci2.data, [-2, 3, 3])
    assert np.allclose(ci3.data, [5, -13, -1, 0])
    assert np.allclose(ci4.data, [-4, -6, -2, -3, -9])

    # Test invalid setting.
    with pytest.raises(ValueError):
        ci1.data = [1, 1, 1]
    with pytest.raises(ValueError):
        ci2.data = [1, 1]


def test_addition(generate_input_list):

    ci1, ci2, ci3, ci4 = generate_input_list

    ci1 += Input(2)
    assert np.allclose(ci1.data, [0, 0])

    res = ci2 + Input(3)
    assert np.allclose(res.data, ci2.data)

    res = ci3 + Input([0, 1, 2, 3])
    assert np.allclose(res.data, [4, 4, 4, 4])

    res = ci4 + Input([-1, -2, -3, -4, -5])
    assert np.allclose(res.data, [0, -1, -1, -1, 0])

    # Test invalid addition.
    with pytest.raises(ValueError):
        ci1 += Input(3)
    with pytest.raises(ValueError):
        res = ci2 + ci3


def test_subtraction(generate_input_list):

    ci1, ci2, ci3, ci4 = generate_input_list

    ci1 -= Input(2)
    assert np.allclose(ci1.data, [0, 0])

    res = ci2 - Input(3)
    assert np.allclose(res.data, ci2.data)

    res = ci3 - Input([3, 2, 1, 0])
    assert np.allclose(res.data, [1, 1, 1, 1])

    res = ci4 - Input([5, -4, 3, -2, 1])
    assert np.allclose(res.data, [-4, 5, -1, 5, 4])

    # Test invalid addition.
    with pytest.raises(ValueError):
        ci1 -= Input(3)
    with pytest.raises(ValueError):
        res = ci2 - ci3


def test_multiplication(generate_input_list):

    ci1, ci2, ci3, ci4 = generate_input_list

    ci1 *= 0
    assert np.allclose(ci1.data, [0, 0])

    res = ci2 * 0
    assert np.allclose(res.data, [0, 0, 0])

    res = ci3 * 3
    assert np.allclose(res.data, [12, 9, 6, 3])

    res = ci4 * (-2)
    assert np.allclose(res.data, [-2, -2, -4, -6, -10])

    # Test commutative property.
    assert np.allclose((ci4 * (-2)).data, ((-2) * ci4).data)


def test_equality(generate_input_list):

    i1, i2, i3, i4 = generate_input_list

    assert i1 == Input([0, 0])
    assert i2 == Input([1, 2, 3])
    assert i1 != i2


def test_repr(generate_input_list):

    for ci in generate_input_list:
        assert isinstance(repr(ci), str)


def test_empty():

    assert not Input(3).is_empty()
    assert Input(0).is_empty()


def test_create_like(generate_input_list):

    for ci in generate_input_list:

        assert Input.create_like(ci).size == ci.size
        assert np.allclose(Input.create_like(ci).data,
                           np.zeros(ci.size))
