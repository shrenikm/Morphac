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
from morphac.simulation.playground import (
    Playground,
    PlaygroundSpec,
)
from morphac.utils.python_utils import MorphacLogicError
from morphac.visualization.map_visualization import canvas_from_map
from morphac.visualization.robot_visualization import RobotVisualizer
from morphac.visualization.playground_visualization import (
    PlaygroundVisualizerSpec,
    PlaygroundVisualizer,
)


class RobotType(Enum):
    ACKERMANN = 0
    DIFFDRIVE = 1
    DUBIN = 2
    TRICYCLE = 3


robot_bank = {
    RobotType.ACKERMANN: Robot(
        kinematic_model=AckermannModel(width=1.0, length=3.0),
        initial_state=State([5.0, 5.0, 0.0, 0.0], []),
    ),
    RobotType.DIFFDRIVE: Robot(
        kinematic_model=DiffdriveModel(radius=0.3, width=1.0),
        initial_state=State([5.0, 5.0, 0.0], []),
    ),
    RobotType.DUBIN: Robot(
        kinematic_model=DubinModel(speed=1.0), initial_state=State([5.0, 5.0, 0.0], [])
    ),
    RobotType.TRICYCLE: Robot(
        kinematic_model=TricycleModel(width=1.0, length=2.0),
        initial_state=State([5.0, 5.0, 0.0, 0.0], []),
    ),
}


def run2(robot_type):

    # Parameters.
    dt = 0.02

    # Get the required robot.
    if robot_type not in robot_bank:
        raise MorphacLogicError("Invalid robot type.")

    robot = robot_bank[robot_type]

    # Create the environment.
    env_map = Map(width=10.0, height=10.0, resolution=0.02)
    canvas = canvas_from_map(env_map)

    # Create the playground.
    playground_spec = PlaygroundSpec("constant_controller_playground", dt)
    playground = Playground(playground_spec, env_map)


def run(robot_type):

    env_map = Map(width=10.0, height=10.0, resolution=0.02)

    canvas = canvas_from_map(env_map)

    robot = robot_bank[robot_type]

    robot_visualizer = RobotVisualizer(env_map.resolution)
    robot_visualizer.visualize(canvas, robot, 0)

    cv2.imshow("Canvas", canvas)
    cv2.waitKey(0)


if __name__ == "__main__":

    # Which robot type to run. One of
    robot_type = RobotType.ACKERMANN

    run2(robot_type)
