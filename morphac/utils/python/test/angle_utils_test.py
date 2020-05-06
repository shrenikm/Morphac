import numpy as np
import pytest

from morphac.utils import to_degrees, to_radians, normalize_angle

# The cpp test checks for actual computation validity. Here we do minimal
# computation checking and focus on testing whether the wrapper works as
# intended.


def test_to_degrees():

    assert np.isclose(to_degrees(0), 0)
    assert np.isclose(to_degrees(np.pi), 180)


def test_to_radians():

    assert np.isclose(to_radians(0), 0)
    assert np.isclose(to_radians(180), np.pi)


def test_normalize_angle():

    assert np.isclose(normalize_angle(0), 0)
    assert np.isclose(normalize_angle(np.pi), np.pi)
    assert np.isclose(normalize_angle(2 * np.pi), 0)
