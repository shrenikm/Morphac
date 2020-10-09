import numpy as np
import pytest

from morphac.constructs import State
from morphac.mechanics.models import (
    KinematicModel,
    AckermannModel,
    DiffdriveModel,
    DubinModel,
    TricycleModel,
)
from morphac.robot.blueprint import Robot, Footprint
from morphac.utils.canvas_utils import create_empty_canvas, paint_canvas
from morphac.utils.python_utils import MorphacVisualizationError
from morphac.visualization.robot_visualization import RobotVisualizer


class CustomKinematicModel(KinematicModel):
    def __init__(self, a, b):

        KinematicModel.__init__(self, 3, 0, 2)
        self.a = a
        self.b = b

    def compute_state_derivative(self, robot_state, control_input):

        der_data = robot_state.data + control_input.data * (self.a + self.b)
        return State(der_data[: self.pose_size], der_data[self.pose_size :])

    def default_footprint(self):
        return Footprint(np.ones([10, 2], dtype=np.float))


@pytest.fixture()
def generate_visualizer_and_canvas():

    return RobotVisualizer(0.01), create_empty_canvas((400, 500))


def test_default_drawing_kernels(generate_visualizer_and_canvas):

    robot_visualizer, canvas = generate_visualizer_and_canvas

    # Make sure that visualization works for the default robot models
    # through the default drawing kernels.
    robots = [
        Robot(AckermannModel(1.0, 1.0)),
        Robot(DiffdriveModel(1.0, 1.0)),
        Robot(DubinModel(1.0)),
        Robot(TricycleModel(1.0, 1.0)),
    ]

    for uid, robot in enumerate(robots):
        robot_visualizer.visualize(canvas, robot, uid)


def test_invalid_default_drawing_kernels(generate_visualizer_and_canvas):

    # Trying to invoke the default kernel on a non default kinematic
    # model should throw an error.
    robot_visualizer, canvas = generate_visualizer_and_canvas

    # Create a robot with a non default kinematic model.
    robot = Robot(CustomKinematicModel(1.0, 1.0))

    with pytest.raises(MorphacVisualizationError):
        robot_visualizer.visualize(canvas, robot, uid=0)


def test_add_drawing_kernel(generate_visualizer_and_canvas):

    robot_visualizer, canvas = generate_visualizer_and_canvas

    # Define the drawing kernel.
    def _drawing_kernel(canvas, robot, resolution):
        paint_canvas(canvas, (1, 1, 1))

    robot = Robot(AckermannModel(1.0, 1.0))
    robot_visualizer.add_drawing_kernel(0, _drawing_kernel)

    # Make sure that the right kernel gets used.
    # As an explicit kernel has been added, it should not be using the
    # default model kernel.
    robot_visualizer.visualize(canvas, robot, 0)
    # The canvas should be painted (0, 0, 0)
    assert np.allclose(canvas, np.ones_like(canvas))


def test_add_drawing_kernel_to_custom_robot(generate_visualizer_and_canvas):

    robot_visualizer, canvas = generate_visualizer_and_canvas

    # Define the drawing kernel.
    def _drawing_kernel(canvas, robot, resolution):
        paint_canvas(canvas, (1, 1, 1))

    # Create a robot with a non default kinematic model.
    robot = Robot(CustomKinematicModel(1.0, 1.0))
    robot_visualizer.add_drawing_kernel(0, _drawing_kernel)

    robot_visualizer.visualize(canvas, robot, 0)
    assert np.allclose(canvas, np.ones_like(canvas))


def test_invalid_add_drawing_to_custom_robot(generate_visualizer_and_canvas):

    # Test the visualize function invoked on an invalid uid on a custom robot.

    robot_visualizer, canvas = generate_visualizer_and_canvas

    # Define the drawing kernel.
    def _drawing_kernel(canvas, robot, resolution):
        paint_canvas(canvas, (1, 1, 1))

    # Create a robot with a non default kinematic model.
    robot = Robot(CustomKinematicModel(1.0, 1.0))
    robot_visualizer.add_drawing_kernel(0, _drawing_kernel)

    # Invoke visualize with an invalid
    with pytest.raises(MorphacVisualizationError):
        robot_visualizer.visualize(canvas, robot, 1)


def test_invalid_add_drawing_kernel(generate_visualizer_and_canvas):

    robot_visualizer, canvas = generate_visualizer_and_canvas

    # Test trying to add an invalid kernel (invalid function signature).
    def _invalid_drawing_kernel(canvas, robot):
        paint_canvas(canvas, (0, 0, 0))

    with pytest.raises(MorphacVisualizationError):
        robot_visualizer.add_drawing_kernel(1, _invalid_drawing_kernel)
