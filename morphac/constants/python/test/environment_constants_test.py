import pytest

from morphac.constants.environment_constants import MapConstants


def test_map_constants():

    assert MapConstants.EMPTY == 0
    assert MapConstants.OBSTACLE == 1


def test_set_map_constants():

    # The values should not be modifiable.

    with pytest.raises(AttributeError):
        MapConstants.EMPTY = 0
    with pytest.raises(AttributeError):
        MapConstants.OBSTACLE = 1
