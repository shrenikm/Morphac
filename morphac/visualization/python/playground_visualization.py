import attr
import cv2
import numpy as np
import time

from morphac.simulation.playground import Playground
from morphac.visualization.map_visualization import canvas_from_map
from morphac.visualization.robot_visualization import RobotVisualizer
from morphac.utils.python_utils import MorphacVisualizationError


@attr.s(frozen=True)
class PlaygroundVisualizerSpec(object):

    display_ratio = attr.ib(type=float, default=1.0)


@attr.s
class PlaygroundVisualizer(object):

    spec = attr.ib(type=PlaygroundVisualizerSpec)
    playground = attr.ib(type=Playground)

    robot_visualizer = attr.ib(type=RobotVisualizer, init=False)

    @robot_visualizer.default
    def _initialize_robot_visualizer(self):
        return RobotVisualizer(self.playground.state.map.resolution)

    # TODO: Not sure if resolution is required.
    _resolution = attr.ib(type=float, init=False)

    @_resolution.default
    def _initialize_resolution(self):
        return self.playground.state.map.resolution

    # Exposing the add drawing kernel functionality.
    def add_robot_drawing_kernel(self, uid, drawing_kernel):
        # The validity check for the kernel happens inside RobotVisualizer.
        self.robot_visualizer.add_drawing_kernel(uid, drawing_kernel)

    def _initialize_window(self):
        cv2.namedWindow(self.playground.spec.name, cv2.WINDOW_KEEPRATIO)

    def _get_visualization_canvas(self):
        canvas = canvas_from_map(self.playground.state.map)

        # Visualize the robots.
        for robot_uid, robot in self.playground.state.robot_oracle.items():
            self.robot_visualizer.visualize(canvas, robot, robot_uid)

        return canvas

    def _resize_canvas(self, canvas):
        return cv2.resize(
            canvas, dsize=None, fx=self.spec.display_ratio, fy=self.spec.display_ratio
        )

    def _visualize(self, visualize):
        canvas = self._get_visualization_canvas()

        # Resize and display.
        canvas = self._resize_canvas(canvas)
        cv2.imshow(self.playground.spec.name, canvas)

        # TODO: Make this delay dynamic
        key = cv2.waitKey(1) & 0xFF

        if key in [ord("q"), 27]:
            return True

        return False

    def _compute_updated_metric(self, metric, metric_type):
        if metric_type == "iters":
            return metric + 1
        else:
            return self.playground.state.time

    def run(self, metric_type="time", metric_limit=np.inf, visualize=True):

        # Note that "time" means simulation time in the playground (dt) and not actual run time.
        if metric_type not in ["iters", "time"]:
            raise MorphacVisualizationError(
                "The metric type must be either 'iters' or 'time'"
            )

        # Keeping track of the actual time.
        start_time = time.time()

        # Simulation metric current value.
        current_metric = 0

        # Initialize the window if visualization is required.
        if visualize:
            self._initialize_window()

        while current_metric < metric_limit:

            # Execute the pilot and update the robot states.
            self.playground.execute()

            # Visualize if the option is set.
            if visualize:
                end_simulation = self._visualize(visualize)
                if end_simulation:
                    break

            # End of all the processing. Update metrics.
            # -------------------------------------------------
            # Update the metric.
            current_metric = self._compute_updated_metric(current_metric, metric_type)

            # Update actual time.
            current_time = time.time() - start_time
