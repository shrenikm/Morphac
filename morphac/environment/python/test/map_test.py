import numpy as np
import pytest

from morphac.environment import Map


@pytest.fixture()
def generate_map_list():

    # List of maps constructed in different ways.
    # Also tests initialization.

    map1 = Map(width=2, height=2, resolution=0.1)
    map2 = Map([[1, 2], [3, 4], [5, 6]], 0.5)
    map3 = Map(((0, 1, 0), (2, -1, 0)), 1)
    map4 = Map(data=np.eye(100), resolution=10)

    return map1, map2, map3, map4


def _is_valid_map_data(map_data):
    if map_data.dtype != np.int32:
        return False
    # Make sure that the map data is row major so that
    # cv2 operations can be applied to it directly.
    if not map_data.flags["C_CONTIGUOUS"]:
        return False
    return True


def test_width(generate_map_list):

    map1, map2, map3, map4 = generate_map_list

    assert np.isclose(map1.width, 2)
    assert np.isclose(map2.width, 1)
    assert np.isclose(map3.width, 3)
    assert np.isclose(map4.width, 1000)

    # Making sure that width is read only.
    with pytest.raises(AttributeError):
        map1.width = 3
    with pytest.raises(AttributeError):
        map2.width = 1


def test_height(generate_map_list):

    map1, map2, map3, map4 = generate_map_list

    assert np.isclose(map1.height, 2)
    assert np.isclose(map2.height, 1.5)
    assert np.isclose(map3.height, 2)
    assert np.isclose(map4.height, 1000)

    # Making sure that height is read only.
    with pytest.raises(AttributeError):
        map1.height = 3
    with pytest.raises(AttributeError):
        map2.height = 1.5


def test_resolution(generate_map_list):

    map1, map2, map3, map4 = generate_map_list

    assert np.isclose(map1.resolution, 0.1)
    assert np.isclose(map2.resolution, 0.5)
    assert np.isclose(map3.resolution, 1)
    assert np.isclose(map4.resolution, 10)

    # Making sure that height is read only.
    with pytest.raises(AttributeError):
        map1.resolution = 1
    with pytest.raises(AttributeError):
        map2.resolution = 0.5


def test_data(generate_map_list):

    map1, map2, map3, map4 = generate_map_list

    # Test getting data.
    assert np.allclose(map1.data, np.zeros((20, 20)))
    assert np.allclose(map2.data, [[1, 2], [3, 4], [5, 6]])
    assert np.allclose(map3.data, [[0, 1, 0], [2, -1, 0]])
    assert np.allclose(map4.data, np.eye(100))

    # Make sure that the data is of the right type and configuration.
    assert _is_valid_map_data(map1.data)
    assert _is_valid_map_data(map2.data)
    assert _is_valid_map_data(map3.data)
    assert _is_valid_map_data(map4.data)

    # Test setting data.
    map1.data = np.ones((20, 20))
    map2.data = np.ones((3, 2))
    map3.data = np.eye(2, 3)
    map4.data = -1 * np.ones((100, 100))

    assert np.allclose(map1.data, np.ones((20, 20)))
    assert np.allclose(map2.data, np.ones((3, 2)))
    assert np.allclose(map3.data, np.eye(2, 3))
    assert np.allclose(map4.data, -1 * np.ones((100, 100)))

    # Test changing the data in place. This uses the get_data_ref() cpp
    # interface.
    map1.data[:, :10] = 0.0
    assert np.allclose(map1.data[:, :10], np.zeros((20, 10)))
    # Make sure that the other values are unchanged
    assert np.allclose(map1.data[:, 10:], np.ones((20, 10)))

    # Test invalid setting.
    with pytest.raises(ValueError):
        map1.data = np.ones((2, 2))
    with pytest.raises(ValueError):
        map2.data = np.ones((2, 3))


def test_evolve(generate_map_list):

    _, map2, _, _ = generate_map_list

    new_map = map2.evolve(data=[[5, 6], [3, 4], [1, 2]])

    assert new_map.width == map2.width
    assert new_map.height == map2.height
    assert new_map.resolution == map2.resolution
    assert np.allclose(new_map.data, [[5, 6], [3, 4], [1, 2]])


def test_invalid_evolve(generate_map_list):

    _, map2, _, _ = generate_map_list

    with pytest.raises(ValueError):
        _ = map2.evolve([[1], [2], [3]])
    with pytest.raises(ValueError):
        _ = map2.evolve([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
