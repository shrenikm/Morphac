import cv2
import numpy as np

from morphac.constructs import State
from morphac.environment import Map
from morphac.mechanics.models import AckermannModel
from morphac.robot.blueprint import Robot, Footprint
from morphac.visualization.map_visualization import canvas_from_map
from morphac.visualization.robot_visualization import RobotVisualizer


def run():

    env_map = Map(width=10., height=10., resolution=0.02)

    canvas = canvas_from_map(env_map)

    robot = Robot(AckermannModel(width=1., length=3.),
                  Footprint.create_rounded_rectangular_footprint(
                      3.5, 1.5, 0., 0.3, 0.1),
                  initial_state=State([5., 5., 0., 0.], [])
                  )

    robot_visualizer = RobotVisualizer(env_map.resolution)
    robot_visualizer.visualize(canvas, robot)

    cv2.imshow('Canvas', canvas)
    cv2.waitKey(0)


if __name__ == "__main__":

    run()
