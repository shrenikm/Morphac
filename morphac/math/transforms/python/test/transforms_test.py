import numpy as np
import pytest

from morphac.math.transforms import (
    canvas_to_world,
    rotate_points,
    rotation_matrix,
    transform_points,
    transformation_matrix,
    translate_points,
    world_to_canvas,
)


@pytest.fixture
def generate_points_list():
    np.random.seed(7)
    points = np.random.randn(10, 2)
    homogeneous_points = np.random.randn(10, 3)

    return points, homogeneous_points

# We don't check the actual value of these computations too much as this is
# done in the cpp tests.


def test_rotation_matrix():

    r = rotation_matrix(angle=0.5)

    assert r.shape == (2, 2)


def test_transformation_matrix():

    t = transformation_matrix(angle=0.5, translation=[2., 3.])

    assert t.shape == (3, 3)
    assert t[2, 2] == 1


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


def test_canvas_to_world():

    world_coord = canvas_to_world(canvas_coord=[100, 200], resolution=0.03)

    assert world_coord.size == 2
    assert world_coord.ndim == 1
    assert world_coord.dtype == np.float64
    assert np.allclose(world_coord, [3., 6.])


def test_world_to_canvas():

    canvas_coord = world_to_canvas(world_coord=[-2., 17.], resolution=0.01)

    assert canvas_coord.size == 2
    assert canvas_coord.ndim == 1
    assert canvas_coord.dtype == np.int32

    # Make sure that the coordinate is valid.
    assert np.allclose(canvas_coord, [-200, 1700])

    # Provide a canvas size and make sure that invalid coordinates are returned
    # as [-1, -1]

    canvas_coord = world_to_canvas(
        world_coord=[-2., 17.], resolution=0.01, canvas_size=(500, 500))

    assert canvas_coord.size == 2
    assert canvas_coord.ndim == 1
    assert canvas_coord.dtype == np.int32
    assert np.allclose(canvas_coord, [-1, -1])
