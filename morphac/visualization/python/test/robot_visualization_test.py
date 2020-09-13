import pytest

from morphac.mechanics.models import (
    AckermannModel,
    DiffdriveModel,
    DubinModel,
    TricycleModel,
)
from morphac.robot.blueprint import Robot
from morphac.visualization.map_visualization import create_empty_canvas
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


def test_add_drawing_kernel():
    robot_visualizer = RobotVisualizer(0.01)
