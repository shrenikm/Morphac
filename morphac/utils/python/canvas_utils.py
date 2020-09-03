import cv2
import numpy as np


def paint_canvas(canvas, color, mask=None):

    assert canvas.ndim == 3
    assert canvas.dtype == np.uint8
    assert len(color) == 3
    if mask is not None:
        assert mask.ndim == 2
        assert mask.dtype == bool
        assert canvas.shape[0] == mask.shape[0]
        assert canvas.shape[1] == mask.shape[1]

    # If mask is None, we paint the entire canvas.
    canvas[..., 0][mask] = color[0]
    canvas[..., 1][mask] = color[1]
    canvas[..., 2][mask] = color[2]


def paint_polygon_using_canvas_coords(canvas, canvas_coords, color):
    # Interchanging x and y while drawing as opencv points requires the x and
    # y axes to be the regular axes, with the origin at the top left.

    coords = np.int32([canvas_coords[:, ::-1]])
    cv2.fillPoly(canvas, coords,
                 color, lineType=cv2.LINE_AA)
