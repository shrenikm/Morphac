import numpy as np
import pytest

from morphac.controllers.basic import ConstantController, ZeroController
from morphac.environment import Map
from morphac.math.numeric import IntegratorType
from morphac.mechanics.models import (
    AckermannModel,
    DiffdriveModel,
    DubinModel,
    TricycleModel,
)
from morphac.robot.blueprint import Robot
from morphac.robot.pilot import Pilot
from morphac.simulation.playground import Playground, PlaygroundSpec
from morphac.utils.canvas_utils import create_empty_canvas, paint_canvas
from morphac.utils.python_utils import MorphacVisualizationError
from morphac.visualization.playground_visualization import (
    PlaygroundVisualizer,
    PlaygroundVisualizerSpec,
)
from morphac.visualization.robot_visualization import RobotVisualizer


# Pilot class for testing..
class ZeroPilot(Pilot):
    def __init__(self, controller):

        Pilot.__init__(self)
        self._controller = controller

    def execute(self, playground_state, uid):

        return self._controller.compute()


@pytest.fixture()
def generate_playground_visualizer():

    env_map = Map(width=20.0, height=20.0, resolution=0.02)

    # Create the playground.
    playground_spec = PlaygroundSpec(name="playground_spec", dt=0.01)
    playground = Playground(playground_spec, env_map)
    robot = Robot(AckermannModel(1.0, 1.0))

    # Construct the pilot.
    pilot = ZeroPilot(ZeroController(2))

    # Add the robot to the playground.
    playground.add_robot(robot, pilot, IntegratorType.EULER_INTEGRATOR, uid=0)

    # Create the playground visualizer.
    spec = PlaygroundVisualizerSpec(display_ratio=1.0)
    playground_visualizer = PlaygroundVisualizer(spec, playground)

    return playground_visualizer


def test_add_robot_drawing_kernel(generate_playground_visualizer):

    playground_visualizer = generate_playground_visualizer

    # Kernel to add.
    def _drawing_kernel(canvas, robot, resolution):
        paint_canvas(canvas, (1, 1, 1))

    # Make sure that the added kernel is used (instead of the default one).
    canvas = create_empty_canvas((500, 500))
    playground_visualizer.add_robot_drawing_kernel(0, _drawing_kernel)
    playground_visualizer.robot_visualizer.visualize(
        canvas, Robot(AckermannModel(1.0, 1.0)), 0
    )

    assert np.allclose(canvas, np.ones_like(canvas))

    # Test invalid kernel.
    def _invalid_drawing_kernel(canvas, robot):
        paint_canvas(canvas, (0, 0, 0))

    with pytest.raises(MorphacVisualizationError):
        playground_visualizer.add_robot_drawing_kernel(1, _invalid_drawing_kernel)


def test_run(generate_playground_visualizer):

    playground_visualizer = generate_playground_visualizer

    # Test both run metrics.
    playground_visualizer.run("time", 5.0, visualize=False)
    playground_visualizer.run("iters", 100, visualize=False)


def test_invalid_run(generate_playground_visualizer):

    playground_visualizer = generate_playground_visualizer

    # Test run with an invalid metric.
    with pytest.raises(MorphacVisualizationError):
        playground_visualizer.run("test", 5.0, visualize=False)

