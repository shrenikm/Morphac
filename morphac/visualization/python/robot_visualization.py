import attr
import cv2
import numpy as np
import time

from morphac.constants import (
    AckermannModelConstants,
    DiffdriveModelConstants,
    DubinModelConstants,
    TricycleModelConstants,
)
from morphac.constants.colors import FlatColors
from morphac.constructs import State
from morphac.mechanics.models import KinematicModel
from morphac.math.geometry import (
    create_rectangular_polygon,
    create_triangular_polygon,
)
from morphac.math.transforms import world_to_canvas, transform_points
from morphac.utils.canvas_utils import paint_polygon_using_canvas_coords
from morphac.utils.mechanics_utils import all_model_class_names
from morphac.utils.python_utils import get_class_name, MorphacLogicError


def _ackermann_drawing_kernel(canvas, robot, resolution):
    def _draw_wheels():
        # TODO: Cache these computations.
        def _compute_wheel_world_coords():
            # wheel coordinates for all four wheels.

            # TODO: Fix incorrect wheel angles when the ideal angle is negative.
            # Inner and outer wheel angles.
            inner_angle, outer_angle = robot.kinematic_model.compute_steering_angles(
                robot.pose[3]
            )

            back_left_wheel = create_rectangular_polygon(
                size_x=wheel_length,
                size_y=wheel_thickness,
                angle=0.0,
                center=[0, width / 2],
            )
            back_right_wheel = create_rectangular_polygon(
                size_x=wheel_length,
                size_y=wheel_thickness,
                angle=0.0,
                center=[0, -width / 2],
            )
            front_left_wheel = create_rectangular_polygon(
                size_x=wheel_length,
                size_y=wheel_thickness,
                angle=inner_angle if robot.pose[3] > 0 else outer_angle,
                center=[length, width / 2],
            )
            front_right_wheel = create_rectangular_polygon(
                size_x=wheel_length,
                size_y=wheel_thickness,
                angle=inner_angle if robot.pose[3] < 0 else outer_angle,
                center=[length, -width / 2],
            )

            return [
                back_left_wheel,
                back_right_wheel,
                front_left_wheel,
                front_right_wheel,
            ]

        # First, we define the coordinates and dimensions in world coordinates.
        wheel_length = length * AckermannModelConstants.DEFAULT_WHEEL_DIAMETER_SCALER
        wheel_thickness = (
            wheel_length / AckermannModelConstants.DEFAULT_WHEEL_SIZE_RATIO
        )

        world_coords = _compute_wheel_world_coords()

        # Paint in the wheels.
        for coords in world_coords:
            coords = transform_points(coords, robot.pose[2], robot.pose.data[:2])
            coords = world_to_canvas(
                world_coords=coords, resolution=resolution, canvas_size=canvas_size
            )
            paint_polygon_using_canvas_coords(canvas, coords, FlatColors.DARK_TEAL)

    def _draw_heading_triangle():
        def _compute_heading_triangle_coords():
            heading_triangle = create_triangular_polygon(
                base=heading_triangle_base,
                height=heading_triangle_height,
                angle=-np.pi / 2,
                center=[length, 0.0],
            )

            return heading_triangle

        # Arbitrary constant to compute the heading triangle size.
        heading_triangle_scaler = 0.2
        heading_triangle_base = min(width, length) * heading_triangle_scaler
        heading_triangle_height = min(width, length) * heading_triangle_scaler

        world_coords = transform_points(
            _compute_heading_triangle_coords(), robot.pose[2], robot.pose.data[:2]
        )

        coords = world_to_canvas(
            world_coords=world_coords, resolution=resolution, canvas_size=canvas_size
        )
        paint_polygon_using_canvas_coords(canvas, coords, FlatColors.DARK_TEAL)

    canvas_size = canvas.shape[:2][::-1]
    length = robot.kinematic_model.length
    width = robot.kinematic_model.width

    footprint_world_coords = transform_points(
        robot.footprint.data, robot.pose[2], robot.pose.data[:2]
    )
    footprint_canvas_coords = world_to_canvas(
        world_coords=footprint_world_coords,
        resolution=resolution,
        canvas_size=canvas_size,
    )

    # Draw the main footprint.
    paint_polygon_using_canvas_coords(canvas, footprint_canvas_coords, FlatColors.TEAL)

    # Draw the wheels.
    _draw_wheels()
    # Draw the triangle that denotes the front of the robot.
    _draw_heading_triangle()


def _diffdrive_drawing_kernel(canvas, robot, resolution):
    def _draw_wheels():
        # TODO: Cache these computations.
        def _compute_wheel_world_coords():
            # wheel coordinates for both wheels.

            left_wheel = create_rectangular_polygon(
                size_x=wheel_length,
                size_y=wheel_thickness,
                angle=0.0,
                center=[0, width / 2],
            )
            right_wheel = create_rectangular_polygon(
                size_x=wheel_length,
                size_y=wheel_thickness,
                angle=0.0,
                center=[0, -width / 2],
            )

            return [
                left_wheel,
                right_wheel,
            ]

        # First, we define the coordinates and dimensions in world coordinates.
        wheel_length = 2 * radius
        wheel_thickness = 2 * radius / DiffdriveModelConstants.DEFAULT_WHEEL_SIZE_RATIO

        world_coords = _compute_wheel_world_coords()

        # Paint in the wheels.
        for coords in world_coords:
            coords = transform_points(coords, robot.pose[2], robot.pose.data[:2])
            coords = world_to_canvas(
                world_coords=coords, resolution=resolution, canvas_size=canvas_size
            )
            paint_polygon_using_canvas_coords(canvas, coords, FlatColors.DARK_PINK)

    def _draw_heading_triangle():
        def _compute_heading_triangle_coords():
            heading_triangle = create_triangular_polygon(
                base=heading_triangle_base,
                height=heading_triangle_height,
                angle=-np.pi / 2,
                center=[width / 2, 0.0],
            )

            return heading_triangle

        # Arbitrary constant to compute the heading triangle size.
        heading_triangle_scaler = 0.2
        heading_triangle_base = width * heading_triangle_scaler
        heading_triangle_height = width * heading_triangle_scaler

        world_coords = transform_points(
            _compute_heading_triangle_coords(), robot.pose[2], robot.pose.data[:2]
        )

        coords = world_to_canvas(
            world_coords=world_coords, resolution=resolution, canvas_size=canvas_size
        )
        paint_polygon_using_canvas_coords(canvas, coords, FlatColors.DARK_PINK)

    canvas_size = canvas.shape[:2][::-1]
    radius = robot.kinematic_model.radius
    width = robot.kinematic_model.width

    footprint_world_coords = transform_points(
        robot.footprint.data, robot.pose[2], robot.pose.data[:2]
    )
    footprint_canvas_coords = world_to_canvas(
        world_coords=footprint_world_coords,
        resolution=resolution,
        canvas_size=canvas_size,
    )

    # Draw the main footprint.
    paint_polygon_using_canvas_coords(canvas, footprint_canvas_coords, FlatColors.PINK)

    # Draw the wheels.
    _draw_wheels()
    # Draw the triangle that denotes the front of the robot.
    _draw_heading_triangle()


def _dubin_drawing_kernel(canvas, robot, resolution):
    def _draw_heading_triangle():
        def _compute_heading_triangle_coords():
            heading_triangle = create_triangular_polygon(
                base=heading_triangle_base,
                height=heading_triangle_height,
                angle=-np.pi / 2,
                center=[height / 2 - heading_triangle_height, 0.0],
            )

            return heading_triangle

        # Arbitrary constant to compute the heading triangle size.
        heading_triangle_scaler = 0.2
        heading_triangle_base = base * heading_triangle_scaler
        heading_triangle_height = height * heading_triangle_scaler

        world_coords = transform_points(
            _compute_heading_triangle_coords(), robot.pose[2], robot.pose.data[:2]
        )

        coords = world_to_canvas(
            world_coords=world_coords, resolution=resolution, canvas_size=canvas_size
        )
        paint_polygon_using_canvas_coords(canvas, coords, FlatColors.DARK_GREEN)

    canvas_size = canvas.shape[:2][::-1]
    base = np.abs(robot.footprint.data[0, 0] - robot.footprint.data[1, 0])
    height = np.abs(robot.footprint.data[1, 1] - robot.footprint.data[2, 1])

    footprint_world_coords = transform_points(
        robot.footprint.data, robot.pose[2], robot.pose.data[:2]
    )
    footprint_canvas_coords = world_to_canvas(
        world_coords=footprint_world_coords,
        resolution=resolution,
        canvas_size=canvas_size,
    )

    # Draw the main footprint.
    paint_polygon_using_canvas_coords(canvas, footprint_canvas_coords, FlatColors.GREEN)
    # Draw the triangle that denotes the front of the robot.
    _draw_heading_triangle()


def _tricycle_drawing_kernel(canvas, robot, resolution):
    def _draw_wheels():
        # TODO: Cache these computations.
        def _compute_wheel_world_coords():
            # wheel coordinates for all four wheels.

            back_left_wheel = create_rectangular_polygon(
                size_x=back_wheel_length,
                size_y=back_wheel_thickness,
                angle=0.0,
                center=[0, width / 2],
            )
            back_right_wheel = create_rectangular_polygon(
                size_x=back_wheel_length,
                size_y=back_wheel_thickness,
                angle=0.0,
                center=[0, -width / 2],
            )
            front_wheel = create_rectangular_polygon(
                size_x=front_wheel_length,
                size_y=front_wheel_thickness,
                angle=robot.pose[3],
                center=[length, 0],
            )

            return [
                back_left_wheel,
                back_right_wheel,
                front_wheel,
            ]

        # Back and front wheel dimensions.
        back_wheel_length = (
            length * TricycleModelConstants.DEFAULT_BACK_WHEEL_DIAMETER_SCALER
        )
        back_wheel_thickness = (
            back_wheel_length / TricycleModelConstants.DEFAULT_BACK_WHEEL_SIZE_RATIO
        )

        front_wheel_length = (
            length * TricycleModelConstants.DEFAULT_FRONT_WHEEL_DIAMETER_SCALER
        )
        front_wheel_thickness = (
            front_wheel_length / TricycleModelConstants.DEFAULT_FRONT_WHEEL_SIZE_RATIO
        )

        world_coords = _compute_wheel_world_coords()

        # Paint in the wheels.
        for coords in world_coords:
            coords = transform_points(coords, robot.pose[2], robot.pose.data[:2])
            coords = world_to_canvas(
                world_coords=coords, resolution=resolution, canvas_size=canvas_size
            )
            paint_polygon_using_canvas_coords(canvas, coords, FlatColors.DARK_ORANGE)

    canvas_size = canvas.shape[:2][::-1]
    width = robot.kinematic_model.width
    length = robot.kinematic_model.length

    footprint_world_coords = transform_points(
        robot.footprint.data, robot.pose[2], robot.pose.data[:2]
    )
    footprint_canvas_coords = world_to_canvas(
        world_coords=footprint_world_coords,
        resolution=resolution,
        canvas_size=canvas_size,
    )

    # Draw the main footprint.
    paint_polygon_using_canvas_coords(
        canvas, footprint_canvas_coords, FlatColors.ORANGE
    )

    # Draw the wheels.
    _draw_wheels()


def _get_model_kernel_correspondence():

    model_class_names = all_model_class_names()
    return {
        model_class_names[0]: _ackermann_drawing_kernel,
        model_class_names[1]: _diffdrive_drawing_kernel,
        model_class_names[2]: _dubin_drawing_kernel,
        model_class_names[3]: _tricycle_drawing_kernel,
    }


@attr.s
class RobotVisualizer(object):

    resolution = attr.ib(type=float)

    # Default drawing kernels for the standard mechanics models.
    _model_kernel_correspondence = attr.ib(
        type=dict, init=False, default=_get_model_kernel_correspondence()
    )

    # Explicit drawing kernels specific to individual robot ids.
    _id_kernel_correspondence = attr.ib(
        type=dict, init=False, default=attr.Factory(dict)
    )

    def add_correspondence(self, robot_id, drawing_kernel):
        assert isinstance(robot_id, int)
        self._id_kernel_correspondence[robot_id] = drawing_kernel

    def visualize(self, canvas, robot, robot_id):
        if robot_id in self._id_kernel_correspondence:
            # First check if the id contains a corresponding drawing kernel.
            # If so, use that.
            self._id_kernel_correspondence[robot_id](canvas, robot, self.resolution)

        elif get_class_name(robot.kinematic_model) in self._model_kernel_correspondence:
            # Otherwise, check if the model contains a corresponding drawing
            # kernel and use that.
            self._model_kernel_correspondence[get_class_name(robot.kinematic_model)](
                canvas, robot, self.resolution
            )
        else:
            # If either the model is non-standard or no id kernel
            # correspondence is provided, raise an error as there is no valid
            # drawing kernel to use.
            raise MorphacLogicError(
                """
                Non standard robot model is used. Please provide an explicit
                drawing kernel using the add_correspondence method.
                """
            )
