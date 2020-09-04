import cv2
from enum import Enum
import numpy as np

from morphac.constructs import State
from morphac.environment import Map
from morphac.mechanics.models import (
    AckermannModel,
    DiffDriveModel,
    DubinModel,
    TricycleModel,
)
from morphac.robot.blueprint import Robot, Footprint
from morphac.visualization.map_visualization import canvas_from_map
from morphac.visualization.robot_visualization import RobotVisualizer


class RobotType(Enum):
    ACKERMANN = 0
    DIFFDRIVE = 1
    DUBIN = 2
    TRICYCLE = 3


def run(robot_type):

    env_map = Map(width=10., height=10., resolution=0.02)

    canvas = canvas_from_map(env_map)

    if robot_type is RobotType.ACKERMANN:

        # Dimensions of the mechanical model.
        length = 2.
        width = 1.
        # Define how much larger the footprint is compared to the length and
        # width of the mechanical model.
        footprint_buffer_x = 0.2 * length
        footprint_buffer_y = 0.2 * width
        # Make sure that the origin of the robot (and hence footprint) is at
        # the mid point of the rear axle.
        robot = Robot(AckermannModel(width, length),
                      Footprint.create_rounded_rectangular_footprint(
            length + 2 * footprint_buffer_x,
            width + 2 * footprint_buffer_y,
            0.,
            min(width, length) / 4,
           0.1,
            relative_center=[-length / 2, 0]),
            initial_state=State([5., 5., 0., 0.], [])
        )

    elif robot_type is RobotType.DIFFDRIVE:

        # Dimensions of the mechanical model.
        radius = 0.5
        width = 1.
        footprint_buffer_x = 0.2 * width
        robot = Robot(DiffDriveModel(radius, width),
                      Footprint.create_circular_footprint(
            width / 2 + footprint_buffer_x,
           0.1
        ),
            initial_state=State([5., 5., 0.], [])
        )
    elif robot_type is RobotType.DUBIN:

       robot = Robot(DubinModel(1.),
                      Footprint.create_triangular_footprint(
           1., 1.5, -np.pi / 2),
            initial_state=State([5., 5., 0.], [])
        )
    elif robot_type is RobotType.TRICYCLE:
        pass
    else:
        raise NotImplementedError

    robot_visualizer = RobotVisualizer(env_map.resolution)
    robot_visualizer.visualize(canvas, robot, 0)

    cv2.imshow('Canvas', canvas)
    cv2.waitKey(0)


if __name__ == "__main__":

    # Which robot type to run. One of
    robot_type = RobotType.DIFFDRIVE

    run(robot_type)
