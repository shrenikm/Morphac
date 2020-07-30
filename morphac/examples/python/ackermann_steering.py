import cv2
import numpy as np

from morphac.environment import Map
from morphac.visualization.map_visualization import canvas_from_map


def run():

    env_map = Map(width=10., height=10., resolution=0.04)

    canvas = canvas_from_map(env_map)
    print(canvas.shape)

    cv2.imshow('Canvas', canvas)
    cv2.waitKey(0)


if __name__ == "__main__":

    run()
