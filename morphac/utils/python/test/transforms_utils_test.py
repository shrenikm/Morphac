import numpy as np
import pytest

from morphac.utils import (
    homogenize_points,
    rotate_points,
    transform_points,
    translate_points,
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
    assert np.allclose(
        homogeneous_points[:, -1], np.ones(homogeneous_points.shape[0]))


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


def test_translate_points(generate_points_list):

    points, _ = generate_points_list

    translated_points = translate_points(points=points, translation=[1., -2.])

    assert isinstance(translated_points, np.ndarray)
    assert translated_points.dtype == np.float64

    assert translated_points.shape == points.shape


def test_invalid_translate_points(generate_points_list):

    points, homogeneous_points = generate_points_list

    with pytest.raises(TypeError):
        _ = translate_points(homogeneous_points, [0., 0.])
    with pytest.raises(TypeError):
        _ = translate_points(points, [0.])
    with pytest.raises(TypeError):
        _ = translate_points(points, [0., 0., 0.])


def test_rotate_points(generate_points_list):

    points, _ = generate_points_list

    rotated_points = rotate_points(points=points, angle=np.pi / 3.)

    assert isinstance(rotated_points, np.ndarray)
    assert rotated_points.dtype == np.float64

    assert rotated_points.shape == points.shape


def test_invalid_rotate_points(generate_points_list):

    points, homogeneous_points = generate_points_list

    with pytest.raises(TypeError):
        _ = rotate_points(homogeneous_points, 0.)


def test_transform_points(generate_points_list):

    points, _ = generate_points_list

    transformed_points = transform_points(
        points=points, angle=np.pi / 3., translation=[1., -2.])

    assert isinstance(transformed_points, np.ndarray)
    assert transformed_points.dtype == np.float64

    assert transformed_points.shape == points.shape


def test_invalid_transform_points(generate_points_list):

    points, homogeneous_points = generate_points_list

    with pytest.raises(TypeError):
        _ = transform_points(homogeneous_points, 0., [0., 0.])
