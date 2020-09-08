import numpy as np
import pytest

from morphac.utils.points_utils import (
    homogenize_points,
    unhomogenize_points,
)


@pytest.fixture
def generate_points_list():
    np.random.seed(7)
    points = np.random.randn(10, 2)
    homogeneous_points = np.random.randn(10, 3)

    return points, homogeneous_points


# As the cpp test does the numeric computation, here we only do some basic
# testing to ensure that the binding interface works correctly.


def test_homogenize_points(generate_points_list):

    points, _ = generate_points_list

    homogeneous_points = homogenize_points(points=points)

    assert isinstance(homogeneous_points, np.ndarray)
    assert homogeneous_points.dtype == np.float64

    assert homogeneous_points.shape == (10, 3)

    assert np.allclose(points, homogeneous_points[:, :2])
    assert np.allclose(homogeneous_points[:, -1], np.ones(homogeneous_points.shape[0]))


def test_invalid_homogenize_points(generate_points_list):

    _, homogeneous_points = generate_points_list

    # Calling the function with an array of incompatible size.
    with pytest.raises(TypeError):
        _ = homogenize_points(points=homogeneous_points)


def test_unhomogenize_points(generate_points_list):

    _, homogeneous_points = generate_points_list

    points = unhomogenize_points(homogeneous_points=homogeneous_points)

    assert isinstance(points, np.ndarray)
    assert points.dtype == np.float64

    assert points.shape == (10, 2)

    assert np.allclose(points, homogeneous_points[:, :2])


def test_invalid_unhomogenize_points(generate_points_list):

    points, _ = generate_points_list

    # Calling the function with an array of incompatible size.
    with pytest.raises(TypeError):
        _ = unhomogenize_points(homogeneous_points=points)
