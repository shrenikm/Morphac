import attr
import cv2
import numpy as np
from typing import List

from morphac.constants.environment_constants import MapConstants
from morphac.constants.colors import MapColors
from morphac.environment import Map
from morphac.math.geometry import (
    CircleShape,
    RectangleShape,
    create_rectangular_polygon,
)
from morphac.math.transforms import world_to_canvas
from morphac.utils.cv2_utils import canvas_to_cv2


# Note that the obstacle adding functions do not mutate the input map.
# Rather it creates a new map with the added obstacle.
# Hence the name 'evolve'
def evolve_map_with_circular_obstacle(env_map, circle_shape):
    env_map_data = np.copy(env_map.data)
    center = canvas_to_cv2(
        world_to_canvas(circle_shape.center, env_map.resolution, env_map.data.shape)
    )
    radius = world_to_canvas(circle_shape.radius, env_map.resolution)
    cv2.circle(env_map_data, tuple(center), radius, MapConstants.OBSTACLE, thickness=-1)

    return env_map.evolve(env_map_data)


def evolve_map_with_rectangular_obstacle(env_map, rectangle_shape):
    env_map_data = np.copy(env_map.data)
    points = canvas_to_cv2(
        world_to_canvas(
            create_rectangular_polygon(rectangle_shape),
            env_map.resolution,
            env_map.data.shape,
        )
    )
    cv2.rectangle(
        env_map_data,
        tuple(points[0]),
        tuple(points[2]),
        MapConstants.OBSTACLE,
        thickness=-1,
    )

    return env_map.evolve(env_map_data)


def evolve_map_with_polygonal_obstacle(env_map, polygon_points):
    env_map_data = np.copy(env_map.data)
    points = canvas_to_cv2(
        world_to_canvas(polygon_points, env_map.resolution, env_map.data.shape,)
    )
    cv2.fillPoly(env_map_data, [points], MapConstants.OBSTACLE, lineType=cv2.LINE_AA)

    return env_map.evolve(env_map_data)
