import numpy as np
import pytest

from morphac.constructs import ControlInput
from morphac.controllers.base import Controller
from morphac.utils.pytest_utils import set_standard_testing_random_seed


class CustomController(Controller):
    def __init__(self, control_input_data):

        Controller.__init__(self)
        self.control_input_data = control_input_data

    def compute(self):

        return ControlInput(self.control_input_data)


@pytest.fixture()
def generate_controller_list():
    set_standard_testing_random_seed()
    c1 = CustomController(np.random.randn(3))
    c2 = CustomController(np.random.randn(6))

    return c1, c2


def test_compute(generate_controller_list):

    c1, c2 = generate_controller_list

    set_standard_testing_random_seed()
    data1 = np.random.randn(3)
    data2 = np.random.randn(6)

    assert np.allclose(c1.compute().data, data1)
    assert np.allclose(c2.compute().data, data2)
