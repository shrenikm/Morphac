import numpy as np
import pytest

from morphac.constructs import ControlInput


@pytest.fixture()
def generate_control_input_list():

    # List of velocities constructed in every single way.
    # This also tests initialization.
    ci1 = ControlInput(size=2)
    ci2 = ControlInput([1, 2, 3])
    ci3 = ControlInput((4, 3, 2, 1))
    ci4 = ControlInput(data=np.array([1, 1, 2, 3, 5], dtype=np.float))

    return ci1, ci2, ci3, ci4


def test_size(generate_control_input_list):

    ci1, ci2, ci3, ci4 = generate_control_input_list

    assert ci1.size == 2
    assert ci2.size == 3
    assert ci3.size == 4
    assert ci4.size == 5

    # Making sure that size is read only.
    with pytest.raises(AttributeError):
        ci1.size = 3
    with pytest.raises(AttributeError):
        ci2.size = 3


def test_data(generate_control_input_list):

    ci1, ci2, ci3, ci4 = generate_control_input_list

    # Test getting data.
    assert np.allclose(ci1.data, [0, 0])
    assert np.allclose(ci2.data, [1.0, 2.0, 3.0])
    assert np.allclose(ci3.data, [4.0, 3.0, 2.0, 1.0])
    assert np.allclose(ci4.data, [1.0, 1.0, 2.0, 3.0, 5.0])

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


def test_getitem(generate_control_input_list):

    ci1, ci2, ci3, ci4 = generate_control_input_list

    for ci in [ci1, ci2, ci3, ci4]:
        for i in range(ci.size):
            assert ci[i] == ci.data[i]
            # Test negative indexing.
            assert ci[-(ci.size - i)] == ci.data[i]

    # Test invalid getitem.
    with pytest.raises(IndexError):
        _ = ci1[-3]
    with pytest.raises(IndexError):
        _ = ci2[3]
    with pytest.raises(IndexError):
        _ = ci3[-5]
    with pytest.raises(IndexError):
        _ = ci4[7]


def test_setitem(generate_control_input_list):

    ci1, ci2, ci3, ci4 = generate_control_input_list
    ci1[0] = 1
    ci2[1] = 1
    ci3[2] = 7
    ci4[0], ci4[-1] = -1, 8

    assert np.allclose(ci1.data, [1, 0])
    assert np.allclose(ci2.data, [1, 1, 3])
    assert np.allclose(ci3.data, [4, 3, 7, 1])
    assert np.allclose(ci4.data, [-1, 1, 2, 3, 8])

    # Test invalid setitem
    with pytest.raises(IndexError):
        ci1[-3] = 0
    with pytest.raises(IndexError):
        ci2[3] = 1
    with pytest.raises(IndexError):
        ci3[-5] = 2
    with pytest.raises(IndexError):
        ci4[7] = 3


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
    with pytest.raises(ValueError):
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
    with pytest.raises(ValueError):
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


def test_equality(generate_control_input_list):

    i1, i2, i3, i4 = generate_control_input_list

    assert i1 == ControlInput([0, 0])
    assert i2 == ControlInput([1, 2, 3])
    assert i1 != i2


def test_repr(generate_control_input_list):

    for ci in generate_control_input_list:
        assert isinstance(repr(ci), str)


def test_empty():

    assert not ControlInput(3).is_empty()
    assert ControlInput(0).is_empty()


def test_create_like(generate_control_input_list):

    for ci in generate_control_input_list:

        assert ControlInput.create_like(control_input=ci).size == ci.size
        assert np.allclose(ControlInput.create_like(ci).data, np.zeros(ci.size))

