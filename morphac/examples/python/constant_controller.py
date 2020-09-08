import cv2
from enum import Enum
import numpy as np

from morphac.constructs import State
from morphac.environment import Map
from morphac.mechanics.models import (
    AckermannModel,
    DiffdriveModel,
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

    env_map = Map(width=10.0, height=10.0, resolution=0.02)

    canvas = canvas_from_map(env_map)

    if robot_type is RobotType.ACKERMANN:
        # Dimensions of the mechanical model.
        width = 1.0
        length = 3.0
        robot = Robot(
            AckermannModel(width, length),
            initial_state=State([5.0, 5.0, 0.0, 0.0], []),
        )
    elif robot_type is RobotType.DIFFDRIVE:
        # Dimensions of the mechanical model.
        radius = 0.3
        width = 1.0
        robot = Robot(
            DiffdriveModel(radius, width), initial_state=State([5.0, 5.0, 0.0], []),
        )
    elif robot_type is RobotType.DUBIN:
        robot = Robot(DubinModel(1.0), initial_state=State([5.0, 5.0, 0.0], []),)
    elif robot_type is RobotType.TRICYCLE:
        # Dimensions of the mechanical model.
        width = 1.0
        length = 2.0
        robot = Robot(
            TricycleModel(width, length), initial_state=State([5.0, 5.0, 0.0, 0.0], []),
        )
    else:
        raise NotImplementedError

    robot_visualizer = RobotVisualizer(env_map.resolution)
    robot_visualizer.visualize(canvas, robot, 0)

    cv2.imshow("Canvas", canvas)
    cv2.waitKey(0)


if __name__ == "__main__":

    # Which robot type to run. One of
    robot_type = RobotType.ACKERMANN

    run(robot_type)
