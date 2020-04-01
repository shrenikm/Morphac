import numpy as np
import pytest

from morphac.constructs import ControlInput


@pytest.fixture()
def generate_control_input_list():

    # List of velocities constructed in every single way.
    # This also tests initialization.
    ci1 = ControlInput(2)
    ci2 = ControlInput([1, 2, 3])
    ci3 = ControlInput((4, 3, 2, 1))
    ci4 = ControlInput(np.array([1, 1, 2, 3, 5], dtype=np.float))

    return ci1, ci2, ci3, ci4


def test_size(generate_control_input_list):

    ci1, ci2, ci3, ci4 = generate_control_input_list

    assert ci1.size == 2
    assert ci2.size == 3
    assert ci3.size == 4
    assert ci4.size == 5


def test_data(generate_control_input_list):

    ci1, ci2, ci3, ci4 = generate_control_input_list

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


def test_addition(generate_control_input_list):

    ci1, ci2, ci3, ci4 = generate_control_input_list

    ci1 += ControlInput(2)
    assert np.allclose(ci1.data, [0, 0])

    res = ci2 + ControlInput(3)
    assert np.allclose(res.data, ci2.data)

    res = ci3 + ControlInput([0, 1, 2, 3])
    assert np.allclose(res.data, [4, 4, 4, 4])

    res = ci4 + ControlInput([-1, -2, -3, -4, -5])
    assert np.allclose(res.data, [0, -1, -1, -1, 0])

    # Test invalid addition.
    with pytest.raises(ValueError):
        ci1 += ControlInput(3)
        res = ci2 + ci3


def test_subtraction(generate_control_input_list):

    ci1, ci2, ci3, ci4 = generate_control_input_list

    ci1 -= ControlInput(2)
    assert np.allclose(ci1.data, [0, 0])

    res = ci2 - ControlInput(3)
    assert np.allclose(res.data, ci2.data)

    res = ci3 - ControlInput([3, 2, 1, 0])
    assert np.allclose(res.data, [1, 1, 1, 1])

    res = ci4 - ControlInput([5, -4, 3, -2, 1])
    assert np.allclose(res.data, [-4, 5, -1, 5, 4])

    # Test invalid addition.
    with pytest.raises(ValueError):
        ci1 -= ControlInput(3)
        res = ci2 - ci3


def test_multiplication(generate_control_input_list):

    ci1, ci2, ci3, ci4 = generate_control_input_list

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


def test_repr(generate_control_input_list):

    for ci in generate_control_input_list:
        assert isinstance(repr(ci), str)


def test_empty():

    assert not ControlInput(3).is_empty()
    assert ControlInput(0).is_empty()


def test_create_like(generate_control_input_list):

    for ci in generate_control_input_list:

        assert ControlInput.create_like(ci).size == ci.size
        assert np.allclose(ControlInput.create_like(ci).data,
                           np.zeros(ci.size))
