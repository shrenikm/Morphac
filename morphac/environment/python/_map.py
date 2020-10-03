import attr
import cv2
import numpy as np
from typing import List

from morphac.constants.environment_constants import MapConstants
from morphac.constants.colors import MapColors
from morphac.environment import Map
from morphac.math.geometry import CircleShape, RectangleShape
from morphac.math.transforms import world_to_canvas


# Note that the obstacle adding functions do not mutate the input map.
# Rather it creates a new map with the added obstacle.
# Hence the name 'evolve'
def evolve_map_with_circular_obstacle(map, circle_shape):
    map_data = np.copy(map.data)
    center = world_to_canvas(circle_shape.center, map.resolution, map.data.shape)
    radius = world_to_canvas(circle_shape.radius, map.resolution)
    cv2.circle(map_data, center, radius, MapConstants.OBSTACLE, thickness=-1)


def evolve_map_with_rectangular_obstacle(map, rectangle_shape):
    pass


def evolve_map_with_polygonal_obstacle(map, polygonal_obstacle):
    pass
