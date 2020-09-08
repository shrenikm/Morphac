import pytest

from morphac.constants import MapConstants


def test_attributes():

    assert MapConstants.EMPTY == 0.0
    assert MapConstants.OBSTACLE == -1.0


def test_invalid_setting():

    # The values should not be modifiable.

    with pytest.raises(AttributeError):
        MapConstants.EMPTY = 1.0
    with pytest.raises(AttributeError):
        MapConstants.OBSTACLE = -1.0
