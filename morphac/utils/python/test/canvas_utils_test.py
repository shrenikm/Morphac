import numpy as np
import pytest

from morphac.utils.canvas_utils import (
    paint_canvas,
    paint_polygon_using_canvas_coords,
)


@pytest.fixture
def empty_canvas():
    return np.zeros([500, 500, 3], dtype=np.uint8)


def test_paint_canvas(empty_canvas):

    # Test painting the entire canvas.
    paint_canvas(empty_canvas, (1, 2, 3))

    assert np.allclose(empty_canvas[..., 0], np.ones(empty_canvas.shape[:2]))
    assert np.allclose(empty_canvas[..., 1], 2 * np.ones(empty_canvas.shape[:2]))
    assert np.allclose(empty_canvas[..., 2], 3 * np.ones(empty_canvas.shape[:2]))

    # Test painting a mask.
    mask = np.zeros(empty_canvas.shape[:2], dtype=np.bool)
    mask[:, :250] = True

    paint_canvas(empty_canvas, (0, 0, 0), mask)

    # The left half of the image must be colored with (0, 0, 0)
    assert np.allclose(empty_canvas[:, :250, 0], np.zeros([500, 250]))
    assert np.allclose(empty_canvas[:, :250, 1], np.zeros([500, 250]))
    assert np.allclose(empty_canvas[:, :250, 2], np.zeros([500, 250]))

    # The right half must be unchanged.
    assert np.allclose(empty_canvas[:, 250:, 0], np.ones([500, 250]))
    assert np.allclose(empty_canvas[:, 250:, 1], 2 * np.ones([500, 250]))
    assert np.allclose(empty_canvas[:, 250:, 2], 3 * np.ones([500, 250]))


def test_paint_polygon_using_canvas_coords(empty_canvas):

    # Polygon to draw
    polygon = np.array([[0, 0], [10, 0], [10, 25]])

    # Making sure that the function executes without any issues.
    paint_polygon_using_canvas_coords(empty_canvas, polygon, (1, 1, 1))

    # Paint the whole canvas using a large polygon.
    #  Making it a bit larger than the polygon to remove any rounded errors.

    polygon = np.array([[-1, -1], [500, -1], [500, 500], [-1, 500]])
    paint_polygon_using_canvas_coords(empty_canvas, polygon, (1, 1, 1))

    assert np.allclose(empty_canvas[..., 0], np.ones(empty_canvas.shape[:2]))
    assert np.allclose(empty_canvas[..., 1], np.ones(empty_canvas.shape[:2]))
    assert np.allclose(empty_canvas[..., 2], np.ones(empty_canvas.shape[:2]))

