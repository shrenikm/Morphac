import numpy as np
import pytest

from morphac.utils.cv2_utils import canvas_to_cv2
from morphac.utils.python_utils import MorphacLogicError


def test_canvas_to_cv2():

    # Make sure that the conversion works for different input types.
    assert np.allclose(canvas_to_cv2([1, 2]), [2, 1])
    assert np.allclose(canvas_to_cv2((1, 2)), [2, 1])
    assert np.allclose(canvas_to_cv2(np.array([10, 11])), [11, 10])
    assert np.allclose(canvas_to_cv2(np.array([[1, 2], [3, 4]])), [[2, 1], [4, 3]])


def test_invalid_canvas_to_cv2():

    with pytest.raises(MorphacLogicError):
        _ = canvas_to_cv2([1, 2, 3])
    with pytest.raises(MorphacLogicError):
        _ = canvas_to_cv2((1, 2, 3))
    with pytest.raises(MorphacLogicError):
        _ = canvas_to_cv2(np.zeros(3))
    with pytest.raises(MorphacLogicError):
        _ = canvas_to_cv2(np.zeros((3, 3)))
