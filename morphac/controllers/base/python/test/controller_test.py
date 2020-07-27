import numpy as np
import pytest

from morphac.constructs import ControlInput
from morphac.controllers import Controller


class CustomController(Controller):
    def __init__(self, control_input_data):

        Controller.__init__(self)
        self.control_input_data = control_input_data

    def compute(self):

        return ControlInput(self.control_input_data)


@pytest.fixture()
def generate_controller_list():
    c1 = CustomController([-1, 2, 3])
    c2 = CustomController([7., 8., 9.])

    return c1, c2


def test_compute(generate_controller_list):

    c1, c2 = generate_controller_list

    assert np.allclose(c1.compute().data, [-1., 2., 3.])
    assert np.allclose(c2.compute().data, [7, 8, 9])
