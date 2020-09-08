import numpy as np
import pytest

from morphac.constructs import ControlInput, State
from morphac.mechanics.models import DubinModel
from morphac.robot.blueprint import Footprint


@pytest.fixture()
def generate_dubin_model_list():

    d1 = DubinModel(1)
    d2 = DubinModel(speed=2.5)

    return d1, d2


def test_speed(generate_dubin_model_list):

    d1, d2 = generate_dubin_model_list

    assert d1.speed == 1.0
    assert d2.speed == 2.5

    # Make sure that speed is read only.
    with pytest.raises(AttributeError):
        d1.speed = 2.0
    with pytest.raises(AttributeError):
        d2.speed = 3.0


def test_size(generate_dubin_model_list):

    d1, d2 = generate_dubin_model_list

    # The sizes are fixed.
    assert d1.pose_size == 3
    assert d2.pose_size == 3

    assert d1.velocity_size == 0
    assert d2.velocity_size == 0

    assert d1.control_input_size == 1
    assert d2.control_input_size == 1

    # Make sure that the sizes are read only.
    with pytest.raises(AttributeError):
        d1.pose_size = 2
    with pytest.raises(AttributeError):
        d2.velocity_size = 0
    with pytest.raises(AttributeError):
        d1.control_input_size = 3


def test_derivative_computation(generate_dubin_model_list):

    d1, d2 = generate_dubin_model_list

    # We only test that the function is called and returns properly, not the
    # actual computation as that cpp side tests this.

    # Test with positional arguments.
    der1 = d1.compute_state_derivative(
        robot_state=State([1, 2, 0], []), control_input=ControlInput(1)
    )

    # In this case, the control input controls the angular velocity and the
    # speed i# constant. Hence the robot must move horizontally (theta=0) with
    # the given speed.
    assert np.allclose(der1.data, [1, 0, 0])

    # Making sure that the derivative can only be computed from control inputs
    # that are of the correct dimensions.
    with pytest.raises(ValueError):
        d1.compute_state_derivative(State(0, 3), ControlInput(1))
    with pytest.raises(ValueError):
        d1.compute_state_derivative(State(3, 1), ControlInput(1))
    with pytest.raises(ValueError):
        d2.compute_state_derivative(State(2, 0), ControlInput(1))
    with pytest.raises(ValueError):
        d2.compute_state_derivative(State(3, 0), ControlInput(2))


def test_normalize_state():

    dubin_model = DubinModel(1)

    # As the cpp side tests the actual computation, we just check that the
    # normalize_state interface works.

    assert dubin_model.normalize_state(robot_state=State(3, 0)) == State(3, 0)


def test_default_footprint(generate_dubin_model_list):

    d1, _ = generate_dubin_model_list

    # Just making sure that the default_footprint function returns a valid footprint.
    assert isinstance(d1.default_footprint(), Footprint)
