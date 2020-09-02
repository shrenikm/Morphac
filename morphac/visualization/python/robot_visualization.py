import attr
import cv2
import numpy as np

from morphac.constants.colors import FlatColors
from morphac.constructs import State
from morphac.mechanics.models import KinematicModel
from morphac.math.geometry import create_rectangular_polygon
from morphac.math.transforms import world_to_canvas, transform_points
from morphac.utils.models_utils import all_model_classes


def _draw_polygon_from_canvas_coords(canvas, canvas_coords, color):
    # Interchanging x and y while drawing as opencv points requires the x and
    # y axes to be the regular axes, with the origin at the top left.

    coords = np.int32([canvas_coords[:, ::-1]])
    cv2.fillPoly(canvas, coords,
                 color, lineType=cv2.LINE_AA)


def _ackermann_drawing_kernel(canvas, robot):

    def _draw_wheels():
        def _compute_wheel_world_coords():
            # wheel coordinates for all four wheels.
            back_left_wheel = create_rectangular_polygon(
                size_x=wheel_length,
                size_y=wheel_thickness,
                angle=0.,
                center=[-length / 2, width / 2]
            )
            back_right_wheel = create_rectangular_polygon(
                size_x=wheel_length,
                size_y=wheel_thickness,
                angle=0.,
                center=[-length / 2, -width / 2]
            )
            front_left_wheel = create_rectangular_polygon(
                size_x=wheel_length,
                size_y=wheel_thickness,
                angle=robot.pose[3],
                center=[length / 2, width / 2]
            )
            front_right_wheel = create_rectangular_polygon(
                size_x=wheel_length,
                size_y=wheel_thickness,
                angle=robot.pose[3],
                center=[length / 2, -width / 2]
            )

            return [
                back_left_wheel,
                back_right_wheel,
                front_left_wheel,
                front_right_wheel
            ]

        # First, we define the coordinates and dimensions in world coordinates.
        length = robot.kinematic_model.length
        width = robot.kinematic_model.width
        wheel_length = length * 0.1
        wheel_thickness = width * 0.1

        wheel_world_coords = _compute_wheel_world_coords()

        for coords in wheel_world_coords:
            coords = transform_points(
                coords,
                robot.pose[2],
                robot.pose.data[:2]
            )
            coords = world_to_canvas(
                world_coords=coords,
                resolution=0.02,
                canvas_size=canvas.shape[:2][::-1]
            )
            _draw_polygon_from_canvas_coords(
                canvas, coords, FlatColors.DARK_TEAL)

    footprint_world_coords = transform_points(
        robot.footprint.data,
        robot.pose[2],
        robot.pose.data[:2])
    footprint_canvas_coords = world_to_canvas(
        world_coords=footprint_world_coords,
        resolution=0.02,
        canvas_size=canvas.shape[:2][::-1]
    )

    # Draw the main footprint.
    _draw_polygon_from_canvas_coords(
        canvas, footprint_canvas_coords, FlatColors.TEAL)

    # Draw the wheels.
    _draw_wheels()


def _diffdrive_drawing_kernel(canvas, robot):
    # Pink
    pass


def _dubin_drawing_kernel(canvas, robot):
    # Green
    pass


def _tricycle_drawing_kernel(canvas, robot):
    # Orange
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
