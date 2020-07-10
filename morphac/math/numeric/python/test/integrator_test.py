import numpy as np
import pytest

from morphac.constructs import ControlInput, State
from morphac.math.numeric import Integrator
from morphac.mechanics.models import DiffDriveModel

# Class that extends from Integrator. Testing if a functional subclass of the
# pybind binding of Integrator can be built.


@pytest.fixture()
def generate_integrator():

    return CustomIntegrator(DiffDriveModel(0.1, 0.2), 2, -1)


class CustomIntegrator(Integrator):

    def __init__(self, kinematic_model, a, b):

        Integrator.__init__(self, kinematic_model)
        self.a = a
        self.b = b

    def step(self, robot_state, control_input, dt):

        updated_state_data = dt * \
            (self.a * robot_state.data + self.b * control_input.data)
        return State(updated_state_data, [])


def test_step_computation(generate_integrator):

    custom_integrator = generate_integrator

    # Testing a and b
    assert custom_integrator.a == 2
    assert custom_integrator.b == -1

    # Testing the actual computation. We make sure that the interface works.

    # Test with positional arguments.
    updated_state = custom_integrator.step(
        State([1, 2, 3, 4], []), ControlInput([1, -1, 2, -3]), 0.1)

    assert np.allclose(updated_state.data, [0.1, 0.5, 0.4, 1.1])


def test_integration(generate_integrator):

    custom_integrator = generate_integrator

    # We don't check the actual value, as the cpp test covers this. We only
    # check if the function calls the base class implementation.

    # Test with positional arguments.
    updated_state = custom_integrator.integrate(robot_state=State(
        [1, 2, 3, 4], []), control_input=ControlInput([1, -1, 2, -3]), time=10, dt=0.01)

    # Making sure that the output state dimensions and configuration is
    # correct.
    assert updated_state.size == 4
    assert updated_state.pose.size == 4
    assert updated_state.is_velocity_empty()
