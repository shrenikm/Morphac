import numpy as np
import pytest

from morphac.robot.blueprint import Footprint


@pytest.fixture()
def generate_footprint_list():

    f1 = Footprint([[1, 2]])
    f2 = Footprint(data=np.ones([10, 2]))

    return f1, f2


@pytest.fixture()
def generate_circular_footprint_list():
    f1 = Footprint.create_circular_footprint(2.0, 0.1)
    f2 = Footprint.create_circular_footprint(
        radius=1.0, angular_resolution=0.01, relative_center=[-4, 4]
    )
    return f1, f2


@pytest.fixture()
def generate_rectangular_footprint_list():
    f1 = Footprint.create_rectangular_footprint(6.0, 4.0, 0.0)
    f2 = Footprint.create_rectangular_footprint(
        size_x=6.0, size_y=4.0, angle=np.pi / 3.0, relative_center=[-4.0, 4.0]
    )
    return f1, f2


@pytest.fixture()
def generate_rounded_rectangular_footprint_list():
    f1 = Footprint.create_rounded_rectangular_footprint(6.0, 4.0, 0.0, 1.0, 0.1)
    f2 = Footprint.create_rounded_rectangular_footprint(
        size_x=6.0,
        size_y=4.0,
        angle=np.pi / 3.0,
        radius=1.0,
        angular_resolution=0.01,
        relative_center=[-4.0, 4],
    )
    return f1, f2


@pytest.fixture()
def generate_triangular_footprint_list():
    f1 = Footprint.create_triangular_footprint(2.0, 2.0, 0.0)
    f2 = Footprint.create_triangular_footprint(
        base=4.0, height=6.0, angle=np.pi / 3.0, relative_center=[-4.0, 4.0]
    )
    return f1, f2


# As the cpp test does the numeric computation, here we only do some basic
# testing to ensure that the binding interface works correctly.


# Tests if the given footprint contains a structurally valid polygon.
def _is_valid_footprint(footprint):

    assert isinstance(footprint.data, np.ndarray)
    assert footprint.data.dtype == np.float64
    assert footprint.data.ndim == 2
    assert footprint.data.shape[1] == 2


def test_invalid_construction():

    # Footprint data must be an nx2 matrix.
    with pytest.raises(ValueError):
        Footprint(np.random.randn(0, 2))


def test_data(generate_footprint_list):

    f1, f2 = generate_footprint_list

    assert np.allclose(f1.data, [[1, 2]])
    assert np.allclose(f2.data, np.ones([10, 2]))

    # Making sure that the data is read only.
    with pytest.raises(AttributeError):
        f1.data = [[3, 4]]
    with pytest.raises(AttributeError):
        f1.data = [[1, 2]]
    with pytest.raises(AttributeError):
        f2.data = np.random.randn(5, 2)
    with pytest.raises(AttributeError):
        f2.data = np.ones([10, 2])


# Testing footprint generators.
def test_circular_footprint(generate_circular_footprint_list):

    f1, f2 = generate_circular_footprint_list

    _is_valid_footprint(f1)
    _is_valid_footprint(f2)


def test_rectangular_footprint(generate_rectangular_footprint_list):

    f1, f2 = generate_rectangular_footprint_list

    _is_valid_footprint(f1)
    _is_valid_footprint(f2)


def test_rounded_rectangular_footprint(generate_rounded_rectangular_footprint_list):

    f1, f2 = generate_rounded_rectangular_footprint_list

    _is_valid_footprint(f1)
    _is_valid_footprint(f2)


def test_triangular_footprint(generate_triangular_footprint_list):

    f1, f2 = generate_triangular_footprint_list

    _is_valid_footprint(f1)
    _is_valid_footprint(f2)
