import numpy as np

from morphac.visualization.colors import MapColors
from morphac.utils.canvas_utils import paint_canvas


def canvas_from_map(environment_map):

    canvas = np.zeros([environment_map.data.shape[0],
                       environment_map.data.shape[1], 3])

    free_space_mask = environment_map.data == 0

    # Paint free space.
    paint_canvas(canvas, free_space_mask, MapColors.WHITE)

    # Paint obstacles.
    # TODO: Modify this accordingly when Map has obstacle passes.
    paint_canvas(canvas, np.logical_not(free_space_mask), MapColors.BLACK)

    return canvas
