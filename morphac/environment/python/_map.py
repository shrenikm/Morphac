import attr
import numpy as np
from typing import List

from morphac.constants.environment_constants import MapConstants
from morphac.constants.colors import MapColors
from morphac.environment import Map


@attr.s(auto_attribs=True, frozen=True)
class CircularObstacle(object):
    radius: float
    center: List


@attr.s(auto_attribs=True, frozen=True)
class RectangularObstacle(object):
    size_x: float
    size_y: float
    center: List


@attr.s(auto_attribs=True, frozen=True)
class PolygonalObstacle(object):
    points: np.ndarray


# Note that the obstacle adding functions do not mutate the input map.
# Rather it creates a new map with the added obstacle.
# Hence the name 'evolve'
def evolve_map_with_circular_obstacle(map, center, radius):
    pass


def evolve_map_with_rectangular_obstacle(map, center, size_x, size_y):
    pass


def evolve_map_with_polygonal_obstacle(map, points):
    pass
