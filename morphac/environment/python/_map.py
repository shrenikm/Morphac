import attr
import cv2
import numpy as np
from typing import List

from morphac.constants.environment_constants import MapConstants
from morphac.constants.colors import MapColors
from morphac.environment import Map
from morphac.math.geometry import CircleShape, RectangleShape
from morphac.math.transforms import world_to_canvas
from morphac.utils.cv2_utils import canvas_to_cv2


# Note that the obstacle adding functions do not mutate the input map.
# Rather it creates a new map with the added obstacle.
# Hence the name 'evolve'
def evolve_map_with_circular_obstacle(env_map, circle_shape):
    env_map_data = np.ascontiguousarray(np.copy(env_map.data))
    center = canvas_to_cv2(
        world_to_canvas(circle_shape.center, env_map.resolution, env_map.data.shape)
    )
    radius = world_to_canvas(circle_shape.radius, env_map.resolution)
    env_map_data = env_map_data.astype(np.uint8)
    cv2.circle(env_map_data, tuple(center), radius, MapConstants.OBSTACLE, thickness=-1)

    return env_map.evolve(env_map_data)


def evolve_map_with_rectangular_obstacle(map, rectangle_shape):
    pass


def evolve_map_with_polygonal_obstacle(map, polygonal_obstacle):
    pass
