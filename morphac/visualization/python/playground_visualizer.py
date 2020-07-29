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

    def run(*, time=None, iters=None):

        assert not (time is not None and iters is not None),
        "Both time and iters arguments cannot be provided"

        # Defining the run metric. For time, it is the elapsed time in seconds.
        # For iters, it is the number of completed iterations.
        current_run_metric = 0

        # If both the value are none, the simulation is run without stopping.
        if time is None and iters is None:
            run_metric_limit = np.inf
        elif time is None:
            run_metric_limit = iters
        else:
            run_metric_limit = time

        while current_run_metric < run_metric_limit:

            pass
