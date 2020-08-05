import cv2
import numpy as np

from morphac.environment import Map
from morphac.visualization.map_visualization import canvas_from_map


def run():

    env_map = Map(width=10., height=10., resolution=0.02)
    env_map.data[50:100, 50:100] = -1

    canvas = canvas_from_map(env_map)

    cv2.imshow('Canvas', canvas)
    cv2.waitKey(0)


if __name__ == "__main__":

    run()
