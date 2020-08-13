import numpy as np
import pytest

from morphac.math.transforms import (
    rotation_matrix,
    transformation_matrix,
    canvas_to_world,
    world_to_canvas,
)

# We don't check the actual value of these computations too much as this is
# done in the cpp tests.


def test_rotation_matrix():

    r = rotation_matrix(angle=0.5)

    assert r.shape == (2, 2)


def test_transformation_matrix():

    t = transformation_matrix(angle=0.5, translation=[2., 3.])

    assert t.shape == (3, 3)
    assert t[2, 2] == 1


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
