import numpy as np
import pytest

from morphac.mechanics.models import (
    AckermannModel,
    DiffdriveModel,
    DubinModel,
    TricycleModel,
)
from morphac.robot.blueprint import Robot
from morphac.utils.canvas_utils import create_empty_canvas, paint_canvas
from morphac.utils.python_utils import MorphacLogicError
from morphac.visualization.robot_visualization import RobotVisualizer


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


def test_add_drawing_kernel(generate_visualizer_and_canvas):
    robot_visualizer, canvas = generate_visualizer_and_canvas

    # Define the drawing kernel.
    def _drawing_kernel(canvas, robot, resolution):
        paint_canvas(canvas, (0, 0, 0))

    robot_visualizer.add_drawing_kernel(0, _drawing_kernel)

    robot = Robot(AckermannModel(1.0, 1.0))

    # Make sure that the right kernel gets used.
    # As an explicit kernel has been added, it should not be using the
    # default model kernel.
    robot_visualizer.visualize(canvas, robot, 0)
    # The canvas should be painted (0, 0, 0)
    assert np.allclose(canvas, np.zeros_like(canvas))

    # Test invalid kernel addition.
    def _invalid_drawing_kernel(canvas, robot):
        paint_canvas(canvas, (0, 0, 0))

    with pytest.raises(MorphacLogicError):
        robot_visualizer.add_drawing_kernel(1, _invalid_drawing_kernel)
