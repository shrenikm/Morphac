import numpy as np
import pytest

from morphac.constructs import Input, State
from morphac.math.numeric import Integrator
from morphac.mechanics.models import DiffDriveModel

# Class that extends from Integrator. Testing if a functional subclass of the
# pybind binding of Integrator can be built.


class CustomIntegrator(Integrator):

    def __init__(self, kinematic_model, a, b):

        Integrator.__init__(self, kinematic_model)
        self.a = a
        self.b = b

    def step(self, robot_state, robot_input, dt):

        return dt * (a * robot_state + b * robot_input)


def test_step_computation():

    custom_integrator = CustomIntegrator(DiffDriveModel(0.1, 0.2), 2, -1)

    # Testing a and b
    assert custom_integrator.a == 2
    assert custom_integrator.b == -1

    # Testing the actual computation. We make sure that the interface works.
    # custom_integrator.step(
