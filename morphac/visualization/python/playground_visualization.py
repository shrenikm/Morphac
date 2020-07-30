import attrs
import numpy as np
import time

from morphac.simulation.playground import Playground


@attr.s(frozen=True)
PlaygroundVisualizerSpec(object):

    display_ratio = attr.ib(type=float, default=1.0)


@attr.s
PlaygroundVisualizer(object):

    _playground = attr.ib(type=Playground)
    _spec = attr.ib(type=PlaygroundVisualizerSpec)

    def run(metric_type='time', metric_limit=np.inf):

        assert metric_type == 'time' or metric_type == 'iters',
        "The metric type must be either 'time' or 'iters'"

        current_metric = 0

        while current_metric < metric_limit:

            pass
