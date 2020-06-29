import numpy as np
import pytest

from morphac.environments import Environment


@pytest.fixture()
def generate_environment_list():

    # List of environments constructed in different ways.
    # Also tests initialization.

    e1 = Environment(width=2, height=2, resolution=0.1)
    e2 = Environment([[1, 2], [3, 4], [5, 6]], 0.5)
    e3 = Environment(((0, 1, 0), (2, -1, 0)), 1)
    e4 = Environment(data=np.eye(100), resolution=10)

    return e1, e2, e3, e4


def test_width(generate_environment_list):

    e1, e2, e3, e4 = generate_environment_list

    assert np.isclose(e1.width, 2)
    assert np.isclose(e2.width, 1)
    assert np.isclose(e3.width, 3)
    assert np.isclose(e4.width, 1000)

    # Making sure that width is read only.
    with pytest.raises(AttributeError):
        e1.width = 3
    with pytest.raises(AttributeError):
        e2.width = 1


def test_height(generate_environment_list):

    e1, e2, e3, e4 = generate_environment_list

    assert np.isclose(e1.height, 2)
    assert np.isclose(e2.height, 1.5)
    assert np.isclose(e3.height, 2)
    assert np.isclose(e4.height, 1000)

    # Making sure that height is read only.
    with pytest.raises(AttributeError):
        e1.height = 3
    with pytest.raises(AttributeError):
        e2.height = 1.5


def test_resolution(generate_environment_list):

    e1, e2, e3, e4 = generate_environment_list

    assert np.isclose(e1.resolution, 0.1)
    assert np.isclose(e2.resolution, 0.5)
    assert np.isclose(e3.resolution, 1)
    assert np.isclose(e4.resolution, 10)

    # Making sure that height is read only.
    with pytest.raises(AttributeError):
        e1.resolution = 1
    with pytest.raises(AttributeError):
        e2.resolution = 0.5


def test_data(generate_environment_list):

    e1, e2, e3, e4 = generate_environment_list

    # Test getting data.
    assert np.allclose(e1.data, np.zeros((20, 20)))
    assert np.allclose(e2.data, [[1, 2], [3, 4], [5, 6]])
    assert np.allclose(e3.data, [[0, 1, 0], [2, -1, 0]])
    assert np.allclose(e4.data, np.eye(100))

    # Test setting data.
    e1.data = np.ones((20, 20))
    e2.data = np.ones((3, 2))
    e3.data = np.eye(2, 3)
    e4.data = -1 * np.ones((100, 100))

    assert np.allclose(e1.data, np.ones((20, 20)))
    assert np.allclose(e2.data, np.ones((3, 2)))
    assert np.allclose(e3.data, np.eye(2, 3))
    assert np.allclose(e4.data, -1 * np.ones((100, 100)))

    # Test invalid setting.
    with pytest.raises(ValueError):
        e1.data = np.ones((2, 2))
    with pytest.raises(ValueError):
        e2.data = np.ones((2, 3))
