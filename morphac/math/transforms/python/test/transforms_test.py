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

from morphac.utils.pytest_utils import set_standard_testing_random_seed


@pytest.fixture
def generate_points_list():
    set_standard_testing_random_seed()
    points = np.random.randn(10, 2)
    homogeneous_points = np.random.randn(10, 3)

    return points, homogeneous_points


# We don't check the actual value of these computations too much as this is
# done in the cpp tests.


def test_rotation_matrix():

    r = rotation_matrix(angle=0.5)

    assert r.shape == (2, 2)


def test_transformation_matrix():

    t = transformation_matrix(angle=0.5, translation=[2.0, 3.0])

    assert t.shape == (3, 3)
    assert t[2, 2] == 1


def test_translate_points(generate_points_list):

    points, _ = generate_points_list

    translated_points = translate_points(points=points, translation=[1.0, -2.0])

    assert isinstance(translated_points, np.ndarray)
    assert translated_points.dtype == np.float64

    assert translated_points.shape == points.shape


def test_invalid_translate_points(generate_points_list):

    points, homogeneous_points = generate_points_list

    with pytest.raises(TypeError):
        _ = translate_points(homogeneous_points, [0.0, 0.0])
    with pytest.raises(TypeError):
        _ = translate_points(points, [0.0])
    with pytest.raises(TypeError):
        _ = translate_points(points, [0.0, 0.0, 0.0])


def test_rotate_points(generate_points_list):

    points, _ = generate_points_list

    rotated_points = rotate_points(points=points, angle=np.pi / 3.0)

    assert isinstance(rotated_points, np.ndarray)
    assert rotated_points.dtype == np.float64

    assert rotated_points.shape == points.shape


def test_invalid_rotate_points(generate_points_list):

    points, homogeneous_points = generate_points_list

    with pytest.raises(TypeError):
        _ = rotate_points(homogeneous_points, 0.0)


def test_transform_points(generate_points_list):

    points, _ = generate_points_list

    transformed_points = transform_points(
        points=points, angle=np.pi / 3.0, translation=[1.0, -2.0]
    )

    assert isinstance(transformed_points, np.ndarray)
    assert transformed_points.dtype == np.float64

    assert transformed_points.shape == points.shape


def test_invalid_transform_points(generate_points_list):

    points, homogeneous_points = generate_points_list

    with pytest.raises(TypeError):
        _ = transform_points(homogeneous_points, 0.0, [0.0, 0.0])


def test_canvas_to_world():

    world_coord = canvas_to_world(
        canvas_coord=[100, 200], resolution=0.03, canvas_size=(200, 200)
    )

    assert world_coord.size == 2
    assert world_coord.ndim == 1
    assert world_coord.dtype == np.float64


def test_canvas_to_world_multiple_points():

    set_standard_testing_random_seed()
    world_coords = canvas_to_world(
        canvas_coords=np.random.randint(200, size=(10, 2)),
        resolution=0.1,
        canvas_size=(200, 200),
    )

    assert world_coords.shape == (10, 2)
    assert world_coords.dtype == np.float64


def test_canvas_to_world_scalar():
    #These must be floats after conversion
    assert isinstance(canvas_to_world(1, 0.01), float)
    assert isinstance(canvas_to_world(50, 0.03), float)

    assert np.isclose(canvas_to_world(1, 0.01), 0.01)
    assert np.isclose(canvas_to_world(50, 0.03), 1.5)


def test_world_to_canvas():

    canvas_coord = world_to_canvas(
        world_coord=[2.0, 17.0], resolution=0.01, canvas_size=(200, 200)
    )

    assert canvas_coord.size == 2
    assert canvas_coord.ndim == 1
    assert canvas_coord.dtype == np.int32


def test_world_to_canvas():
    set_standard_testing_random_seed()
    world_coords = np.random.randn(10, 2)
    canvas_coords = world_to_canvas(
        world_coords=world_coords, resolution=0.1, canvas_size=(200, 200)
    )

    assert canvas_coords.shape == (10, 2)
    assert canvas_coords.dtype == np.int32


def test_world_to_canvas_scalar():

    # These must be integers after conversion.
    assert isinstance(world_to_canvas(1.0, 0.01), int)
    assert isinstance(world_to_canvas(1.015, 0.02),int)
    assert isinstance(world_to_canvas(1.005, 0.02),int)

    assert world_to_canvas(1.0, 0.01) == 100
    assert world_to_canvas(1.015, 0.02) == 51
    assert world_to_canvas(1.005, 0.02) == 50
