import pytest

from morphac.constructs import ControlInput, State
from morphac.math.numeric import RK4Integrator
from morphac.mechanics.models import DiffdriveModel


@pytest.fixture()
def generate_integrator():

    return RK4Integrator(DiffdriveModel(0.1, 0.2))


def test_step_computation(generate_integrator):

    rk4_integrator = generate_integrator

    # We don't check the actual computation as the cpp test covers this. We
    # only check if the function calls and returns properly.

    # Test with positional arguments.
    updated_state = rk4_integrator.step(
        robot_state=State([1, 2, 0], []),
        control_input=ControlInput([1, -1]),
        dt=0.1
    )

    assert updated_state.size == 3
    assert updated_state.pose.size == 3
    assert updated_state.is_velocity_empty()


def test_integration(generate_integrator):

    rk4_integrator = generate_integrator

    # We don't check the actual value, as the cpp test covers this. We only
    # check if the function calls the base class implementation.

    # Test with positional arguments.
    updated_state = rk4_integrator.integrate(
        robot_state=State([1, 2, 0], []),
        control_input=ControlInput([1, -1]),
        time=10,
        dt=0.01
    )

    # Making sure that the output state dimensions and configuration is
    # correct.
    assert updated_state.size == 3
    assert updated_state.pose.size == 3
    assert updated_state.is_velocity_empty()
