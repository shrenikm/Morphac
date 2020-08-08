import numpy as np
import pytest

from morphac.constructs import ControlInput, State
from morphac.mechanics.models import AckermannModel


@pytest.fixture()
def generate_ackermann_model_list():

    a1 = AckermannModel(1, 2)
    a2 = AckermannModel(width=1.5, length=6.)

    return a1, a2


def test_invalid_construction():

    # Width and length must both be positive.
    with pytest.raises(ValueError):
        _ = AckermannModel(0., 2.)
    with pytest.raises(ValueError):
        _ = AckermannModel(2., 0.)
    with pytest.raises(ValueError):
        _ = AckermannModel(-1., 2.)
    with pytest.raises(ValueError):
        _ = AckermannModel(1., -2.)


def test_width(generate_ackermann_model_list):

    a1, a2 = generate_ackermann_model_list

    assert a1.width == 1.
    assert a2.width == 1.5

    # Make sure that width is read only.
    with pytest.raises(AttributeError):
        a1.width = 2.
    with pytest.raises(AttributeError):
        a2.width = 3.


def test_length(generate_ackermann_model_list):

    a1, a2 = generate_ackermann_model_list

    assert a1.length == 2.
    assert a2.length == 6.

    # Make sure that length is read only.
    with pytest.raises(AttributeError):
        a1.length = 4.
    with pytest.raises(AttributeError):
        a2.length = 5.


def test_size(generate_ackermann_model_list):

    a1, a2 = generate_ackermann_model_list

    # The sizes are fixed.
    assert a1.pose_size == 4
    assert a2.pose_size == 4

    assert a1.velocity_size == 0
    assert a2.velocity_size == 0

    assert a1.control_input_size == 2
    assert a2.control_input_size == 2

    # Make sure that these are read only.
    with pytest.raises(AttributeError):
        a1.pose_size = 2
    with pytest.raises(AttributeError):
        a2.velocity_size = 0
    with pytest.raises(AttributeError):
        a1.control_input_size = 3


def test_derivative_computation(generate_ackermann_model_list):

    a1, a2 = generate_ackermann_model_list

    # We only test that the function is called and returns properly, not the
    # actual computation as the cpp side tests this.

    # Test with positional arguments.
    der1 = a1.compute_state_derivative(
        robot_state=State([1, 2, 0, 0], []), control_input=ControlInput(2))

    assert np.allclose(der1.data, [0, 0, 0, 0])

    # Making sure that the derivative can only be computed from control inputs
    # that are of the correct dimensions.
    with pytest.raises(ValueError):
        a1.compute_state_derivative(State(0, 4), ControlInput(2))
    with pytest.raises(ValueError):
        a1.compute_state_derivative(State(4, 1), ControlInput(2))
    with pytest.raises(ValueError):
        a2.compute_state_derivative(State(3, 0), ControlInput(2))
    with pytest.raises(ValueError):
        a2.compute_state_derivative(State(4, 0), ControlInput(3))

    # It should also throw an exception if the steering angle is invalid.
    with pytest.raises(ValueError):
        a1.compute_state_derivative(
            State([0., 0., 0., 2 * np.pi / 3], []), ControlInput(2))
    with pytest.raises(ValueError):
        a1.compute_state_derivative(
            State([0., 0., np.pi / 2, -2 * np.pi / 3], []), ControlInput(2))


def test_compute_steering_angles(generate_ackermann_model_list):

    a1, a2 = generate_ackermann_model_list

    # This relation must always follow:
    # Outer angle < ideal angle < inner angle
    ideal_steering_angle = np.pi / 4.
    inner_steering_angle = a1.compute_inner_steering_angle(
        ideal_steering_angle)
    outer_steering_angle = a1.compute_outer_steering_angle(
        ideal_steering_angle)

    assert outer_steering_angle < ideal_steering_angle < inner_steering_angle

    # Test for a negative ideal angle. Also make sure that the function that
    # returns both inner and outer values works.
    ideal_steering_angle = -np.pi / 4.
    inner_steering_angle, outer_steering_angle = a2.compute_steering_angles(
        ideal_steering_angle)

    assert outer_steering_angle < ideal_steering_angle < inner_steering_angle


def test_normalize_state():

    ackermann_model = AckermannModel(1, 1)

    # As the cpp side tests the actual computation, we just check that the
    # normalize_state interface works.

    assert ackermann_model.normalize_state(
        robot_state=State(4, 0)) == State(4, 0)
