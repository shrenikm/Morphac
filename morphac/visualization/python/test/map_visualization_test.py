import numpy as np

from morphac.constants.colors import MapColors
from morphac.constants.environment_constants import MapConstants
from morphac.environment import Map
from morphac.visualization.map_visualization import canvas_from_map


def _valid_canvas(canvas):

    assert canvas.ndim == 3
    assert canvas.dtype == np.uint8
    assert canvas.shape[2] == 3


def test_canvas_from_map_without_obstacles():

    env_map = Map(width=20, height=20, resolution=0.01)

    canvas = canvas_from_map(env_map)

    # Make sure that the canvas is valid.
    _valid_canvas(canvas)


def test_canvas_from_map_with_obstacles():

    map_data = MapConstants.EMPTY * np.ones([1000, 1000], dtype=np.uint8)
    # Left half of the map as an obstacle.
    map_data[:, :500] = MapConstants.OBSTACLE

    env_map = Map(map_data, resolution=0.01)

    canvas = canvas_from_map(env_map)

    _valid_canvas(canvas)

    # Making sure that the canvas is painted correctly.
    for i in range(3):
        np.allclose(canvas[:, :500, i], MapColors.BLACK[i] * np.ones([1000, 500]))
        np.allclose(canvas[:, 500:, i], MapColors.WHITE[i] * np.ones([1000, 500]))
