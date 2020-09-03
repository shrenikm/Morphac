import attr
import cv2
import numpy as np
import time

from morphac.constants.colors import FlatColors
from morphac.constructs import State
from morphac.mechanics.models import KinematicModel
from morphac.math.geometry import (
    create_rectangular_polygon,
    create_triangular_polygon,
)
from morphac.math.transforms import world_to_canvas, transform_points
from morphac.utils.canvas_utils import paint_polygon_using_canvas_coords
from morphac.utils.models_utils import all_model_classes
from morphac.utils.python_utils import get_class_name


def _ackermann_drawing_kernel(canvas, robot, resolution):

    def _draw_wheels():
        # TODO: Cache these computations.
        def _compute_wheel_world_coords():
            # wheel coordinates for all four wheels.

            # TODO: Fix incorrect wheel angles when the ideal angle is negative.
            # Inner and outer wheel angles.
            inner_angle, outer_angle = \
                robot.kinematic_model.compute_steering_angles(robot.pose[3])

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
                angle=inner_angle if robot.pose[3] > 0 else outer_angle,
                center=[length / 2, width / 2]
            )
            front_right_wheel = create_rectangular_polygon(
                size_x=wheel_length,
                size_y=wheel_thickness,
                angle=inner_angle if robot.pose[3] < 0 else outer_angle,
                center=[length / 2, -width / 2]
            )

            return [
                back_left_wheel,
                back_right_wheel,
                front_left_wheel,
                front_right_wheel
            ]

        # First, we define the coordinates and dimensions in world coordinates.
        wheel_length = length * 0.2
        wheel_thickness = wheel_length / 2.5

        world_coords = _compute_wheel_world_coords()

        # Paint in the wheels.
        for coords in world_coords:
            coords = transform_points(
                coords,
                robot.pose[2],
                robot.pose.data[:2]
            )
            coords = world_to_canvas(
                world_coords=coords,
                resolution=resolution,
                canvas_size=canvas_size
            )
            paint_polygon_using_canvas_coords(
                canvas, coords, FlatColors.DARK_TEAL)

    def _draw_heading_triangle():
        def _compute_heading_triangle_coords():
            heading_triangle = create_triangular_polygon(
                base=heading_triangle_base,
                height=heading_triangle_height,
                angle=-np.pi / 2,
                center=[length / 2, 0.]
            )

            return heading_triangle

        heading_triangle_base = width * 0.2
        heading_triangle_height = width * 0.2

        world_coords = transform_points(
            _compute_heading_triangle_coords(),
            robot.pose[2],
            robot.pose.data[:2]
        )

        coords = world_to_canvas(
            world_coords=world_coords,
            resolution=resolution,
            canvas_size=canvas_size
        )
        paint_polygon_using_canvas_coords(canvas, coords, FlatColors.DARK_TEAL)

    canvas_size = canvas.shape[:2][::-1]
    length = robot.kinematic_model.length
    width = robot.kinematic_model.width

    footprint_world_coords = transform_points(
        robot.footprint.data,
        robot.pose[2],
        robot.pose.data[:2]
    )
    footprint_canvas_coords = world_to_canvas(
        world_coords=footprint_world_coords,
        resolution=resolution,
        canvas_size=canvas_size
    )

    # Draw the main footprint.
    paint_polygon_using_canvas_coords(
        canvas, footprint_canvas_coords, FlatColors.TEAL)

    # Draw the wheels.
    _draw_wheels()
    _draw_heading_triangle()


def _diffdrive_drawing_kernel(canvas, robot):
    # Pink
    pass


def _dubin_drawing_kernel(canvas, robot, resolution):

    canvas_size = canvas.shape[:2][::-1]

    footprint_world_coords = transform_points(
        robot.footprint.data,
        robot.pose[2],
        robot.pose.data[:2]
    )
    footprint_canvas_coords = world_to_canvas(
        world_coords=footprint_world_coords,
        resolution=resolution,
        canvas_size=canvas_size
    )

    # Draw the main footprint.
    paint_polygon_using_canvas_coords(
        canvas, footprint_canvas_coords, FlatColors.GREEN)


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

    resolution = attr.ib(type=float)

    _model_kernel_correspondence = attr.ib(
        type=dict,
        init=False,
        default=_get_model_kernel_correspondence()
    )

    def add_correspondence(self, model_class_name, drawing_kernel):
        assert isinstance(model_class, KinematicModel)
        self._model_kernel_correspondence[model_class_name] = drawing_kernel

    def visualize(self, canvas, robot):
        # Get the drawing kernel from the model and draw the robot on the
        # canvas.
        self._model_kernel_correspondence[get_class_name(
            robot.kinematic_model)](canvas, robot, self.resolution)
