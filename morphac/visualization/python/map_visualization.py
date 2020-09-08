import numpy as np

from morphac.constants import MapConstants
from morphac.constants.colors import MapColors
from morphac.utils.canvas_utils import paint_canvas


def canvas_from_map(environment_map):

    canvas = np.zeros(
        [environment_map.data.shape[0], environment_map.data.shape[1], 3],
        dtype=np.uint8,
    )

    obstacle_space_mask = environment_map.data == MapConstants.OBSTACLE

    # Paint the entire canvas as empty space first.
    paint_canvas(canvas, MapColors.WHITE)

    # Paint obstacles.
    # TODO: Modify this accordingly when Map has obstacle passes.
    paint_canvas(canvas, MapColors.BLACK, obstacle_space_mask)

    return canvas
