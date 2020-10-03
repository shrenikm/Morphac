import numpy as np
from morphac.utils.python_utils import MorphacLogicError


def canvas_to_cv2(canvas_coords):
    # Opencv coordinates are canvas coordinates with interchanged x and y components.
    # This is because points requires the x and y axes to be the regular axes,
    # with the origin at the top left.
    canvas_coords = np.array(canvas_coords, dtype=np.int32)
    if canvas_coords.ndim == 1:
        if len(canvas_coords) != 2:
            raise MorphacLogicError("Invalid coordinate size.")
        return canvas_coords[::-1]
    elif canvas_coords.ndim == 2:
        if canvas_coords.shape[1] != 2:
            raise MorphacLogicError("Invalid coordinate size.")
        return canvas_coords[:, ::-1]
    else:
        raise MorphacLogicError("Invalid coordinate dimensions.")
