import cv2
import numpy as np

from morphac.constructs import State
from morphac.environment import Map
from morphac.mechanics.models import AckermannModel
from morphac.robot.blueprint import Robot, Footprint
from morphac.visualization.map_visualization import canvas_from_map
from morphac.visualization.robot_visualization import _ackermann_drawing_kernel


def run():

    env_map = Map(width=10., height=10., resolution=0.02)
    env_map.data[50:100, 50:100] = -1

    canvas = canvas_from_map(env_map)

    robot = Robot(AckermannModel(width=1., length=3.),
                  #Footprint.create_circular_footprint(2., 0.1),
                  #Footprint.create_rectangular_footprint(4., 2., 0.),
                  # Footprint.create_rounded_rectangular_footprint(
                  #    4., 2., 0., 0.5, 0.1),
                  Footprint.create_triangular_footprint(3., 4., 0.),
                  initial_state=State([5., 5., 0., 0.], [])
                  )

    _ackermann_drawing_kernel(canvas, robot)

    cv2.imshow('Canvas', canvas)
    cv2.waitKey(0)


if __name__ == "__main__":

    run()
