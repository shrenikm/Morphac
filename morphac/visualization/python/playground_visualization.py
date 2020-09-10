import attr
import numpy as np
import time

from morphac.simulation.playground import Playground
from morphac.visualization.robot_visualization import RobotVisualizer
from morphac.utils.python_utils import MorphacLogicError


@attr.s(frozen=True)
class PlaygroundVisualizerSpec(object):

    display_ratio = attr.ib(type=float, default=1.0)


@attr.s
class PlaygroundVisualizer(object):

    _playground = attr.ib(type=Playground)
    _spec = attr.ib(type=PlaygroundVisualizerSpec)

    def run(metric_type="time", metric_limit=np.inf):

        if metric_type not in ["iters", "time"]:
            raise MorpahcLogicError("The metric type must be either 'iters' or 'time'")

        current_metric = 0

        while current_metric < metric_limit:

            pass
