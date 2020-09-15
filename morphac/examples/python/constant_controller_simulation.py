from argparse import ArgumentParser, RawTextHelpFormatter
import cv2
from enum import Enum
import numpy as np

from morphac.constructs import State
from morphac.controllers.basic import ConstantController
from morphac.environment import Map
from morphac.math.numeric import IntegratorType
from morphac.mechanics.models import (
    AckermannModel,
    DiffdriveModel,
    DubinModel,
    TricycleModel,
)
from morphac.robot.blueprint import Robot, Footprint
from morphac.robot.pilot import Pilot
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
    ACKERMANN = "ackermann"
    DIFFDRIVE = "diffdrive"
    DUBIN = "dubin"
    TRICYCLE = "tricycle"


robot_bank = {
    RobotType.ACKERMANN: Robot(
        kinematic_model=AckermannModel(width=1.0, length=3.0),
        initial_state=State([10.0, 5.0, 0.0, np.pi / 6], []),
    ),
    RobotType.DIFFDRIVE: Robot(
        kinematic_model=DiffdriveModel(radius=0.3, width=1.0),
        initial_state=State([10.0, 5.0, 0.0], []),
    ),
    RobotType.DUBIN: Robot(
        kinematic_model=DubinModel(speed=1.0), initial_state=State([10.0, 5.0, 0.0], [])
    ),
    RobotType.TRICYCLE: Robot(
        kinematic_model=TricycleModel(width=1.0, length=2.0),
        initial_state=State([10.0, 5.0, 0.0, np.pi / 8], []),
    ),
}

constant_control_bank = {
    RobotType.ACKERMANN: [1.0, 0.0],
    RobotType.DIFFDRIVE: [1.6, 2.0],
    RobotType.DUBIN: [0.2],
    RobotType.TRICYCLE: [1.0, 0.0],
}

# Constant pilot class.
class ConstantPilot(Pilot):
    def __init__(self, controller):

        Pilot.__init__(self)
        self._controller = controller

    def execute(self, playground_state, uid):

        return self._controller.compute()


def main(robot_type):

    # Parameters.
    dt = 0.02
    display_ratio = 1.0
    metric_type = "time"
    metric_limit = 100.0

    # Create the environment.
    env_map = Map(width=20.0, height=20.0, resolution=0.02)

    # Create the playground.
    playground_spec = PlaygroundSpec(name="constant_controller_playground", dt=dt)
    playground = Playground(playground_spec, env_map)

    # Get the required robot.
    if robot_type not in robot_bank:
        raise MorphacLogicError("Invalid robot type.")

    robot = robot_bank[robot_type]

    # Construct the pilot.
    pilot = ConstantPilot(ConstantController(constant_control_bank[robot_type]))

    # Add the robot to the playground.
    playground.add_robot(robot, pilot, IntegratorType.EULER_INTEGRATOR, uid=0)

    # Create the playground visualizer.
    playground_visualizer_spec = PlaygroundVisualizerSpec(display_ratio=display_ratio)
    playground_visualizer = PlaygroundVisualizer(
        spec=playground_visualizer_spec, playground=playground
    )

    playground_visualizer.run(metric_type, metric_limit)


if __name__ == "__main__":

    parser = ArgumentParser(
        description="Simulation of a robot given constant control inputs.",
        formatter_class=RawTextHelpFormatter,
    )
    parser.add_argument(
        "-r",
        "--robot_type",
        default="ackermann",
        type=str,
        help="Type of robot to use. The available options are: \n1. ackermann\n2. diffdrive\n3. dubin\n4. tricycle",
    )
    args = parser.parse_args()

    try:
        robot_type = RobotType(args.robot_type)
    except (ValueError):
        raise MorphacLogicError("Invalid robot type. Please try again.")

    # Which robot type to run. One of
    main(RobotType(args.robot_type))
