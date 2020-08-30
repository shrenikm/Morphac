import attr
import cv2
import numpy as np

from morphac.constructs import State
from morphac.mechanics.models import KinematicModel
from morphac.math.transforms import world_to_canvas, transform_points
from morphac.utils.models_utils import all_model_classes


def _ackermann_drawing_kernel(canvas, robot):
    footprint_world_coords = transform_points(
        robot.footprint.data,
        robot.pose[2],
        robot.pose.data[:2])
    footprint_world_coords = world_to_canvas(
        world_coords=footprint_world_coords,
        resolution=0.02,
        canvas_size=(canvas.shape[1], canvas.shape[0])
    )
    footprint_world_coords = np.int32([footprint_world_coords])
    cv2.fillPoly(canvas, footprint_world_coords,
                 (20, 200, 10), lineType=cv2.LINE_AA)


def _diffdrive_drawing_kernel(canvas, robot):
    pass


def _dubin_drawing_kernel(canvas, robot):
    pass


def _tricycle_drawing_kernel(canvas, robot):
    pass


def _get_model_kernel_correspondence():
    model_classes = all_model_classes()
    return {
        model_classes[0]: _ackermann_drawing_kernel,
        model_classes[1]: _diffdrive_drawing_kernel,
        model_classes[2]: _dubin_drawing_kernel,
        model_classes[3]: _tricycle_drawing_kernel,
    }


@attr.s
class RobotVisualizer(object):

    _model_kernel_correspondence = attr.ib(
        type=dict,
        init=False,
        default=_get_model_kernel_correspondence()
    )

    def add_correspondence(model_class, drawing_kernel):
        assert isinstance(model_class, KinematicModel)
        self._model_kernel_correspondence[model_class] = drawing_kernel
