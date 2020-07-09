import numpy as np
import pytest

from morphac.constructs import Input
from morphac.environment import Map
from morphac.robot.driver import Pilot
from morphac.simulation.playground import PlaygroundState


class CustomPilot(Pilot):

    def __init__(self, input_data):

        Pilot.__init__(self)
        self.input_data = input_data

    def execute(self, playground_state, uid):

        return Input(self.input_data)


@pytest.fixture()
def generate_pilot_list():
    p1 = CustomPilot([1, 2, 3])
    p2 = CustomPilot(np.ones(10))

    return p1, p2


def test_execute(generate_pilot_list):

    # Make sure that the derived Pilot class performs the right operation
    # during an execute call.
    p1, p2 = generate_pilot_list

    # PlaygroundState object to be used.
    playground_state = PlaygroundState(Map(10, 10, 1.))

    assert np.allclose(p1.execute(playground_state, 0).data, [1, 2, 3])
    assert np.allclose(p2.execute(playground_state, 0).data, [1] * 10)
