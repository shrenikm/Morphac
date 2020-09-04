import numpy as np
import pytest

from morphac.constructs import ControlInput, State
from morphac.mechanics.models import DiffDriveModel


@pytest.fixture()
def generate_diffdrive_model_list():

    d1 = DiffDriveModel(1, 2)
    d2 = DiffDriveModel(radius=1.5, width=6.)

    return d1, d2


def test_invalid_construction():

    # Radius and width must both be positive.
    with pytest.raises(ValueError):
        _ = DiffDriveModel(0., 2.)
    with pytest.raises(ValueError):
        _ = DiffDriveModel(2., 0.)
    with pytest.raises(ValueError):
        _ = DiffDriveModel(-1., 2.)
    with pytest.raises(ValueError):
        _ = DiffDriveModel(1., -2.)


def test_radius(generate_diffdrive_model_list):

    d1, d2 = generate_diffdrive_model_list

    assert d1.radius == 1.
    assert d2.radius == 1.5

    # Make sure that radius is read only.
    with pytest.raises(AttributeError):
        d1.radius = 2.
    with pytest.raises(AttributeError):
        d2.radius = 3.


def test_width(generate_diffdrive_model_list):

    d1, d2 = generate_diffdrive_model_list

    assert d1.width == 2.
    assert d2.width == 6.

    # Make sure that width is read only.
    with pytest.raises(AttributeError):
        d1.width = 4.
    with pytest.raises(AttributeError):
        d2.width = 5.


def test_size(generate_diffdrive_model_list):

    d1, d2 = generate_diffdrive_model_list

    # The sizes are fixed.
    assert d1.pose_size == 3
    assert d2.pose_size == 3

    assert d1.velocity_size == 0
    assert d2.velocity_size == 0

    assert d1.control_input_size == 2
    assert d2.control_input_size == 2

    # Make sure that these are read only.
    with pytest.raises(AttributeError):
        d1.pose_size = 2
    with pytest.raises(AttributeError):
        d2.velocity_size = 0
    with pytest.raises(AttributeError):
        d1.control_input_size = 3


def test_derivative_computation(generate_diffdrive_model_list):

    d1, d2 = generate_diffdrive_model_list

    # We only test that the function is called and returns properly, not the
    # actual computation as the cpp side tests this.

    # Test with positional arguments.
    der1 = d1.compute_state_derivative(
        robot_state=State([1, 2, 3], []), control_input=ControlInput(2))

    assert np.allclose(der1.data, [0, 0, 0])

    # Making sure that the derivative can only be computed from control inputs
    # that are of the correct dimensions.
    with pytest.raises(ValueError):
        d1.compute_state_derivative(State(0, 3), ControlInput(2))
    with pytest.raises(ValueError):
        d1.compute_state_derivative(State(3, 1), ControlInput(2))
    with pytest.raises(ValueError):
        d2.compute_state_derivative(State(2, 0), ControlInput(2))
    with pytest.raises(ValueError):
        d2.compute_state_derivative(State(3, 0), ControlInput(3))


def test_normalize_state():

    diffdrive_model = DiffDriveModel(1, 1)

    # As the cpp side tests the actual computation, we just check that the
    # normalize_state interface works.

    assert diffdrive_model.normalize_state(
        robot_state=State(3, 0)) == State(3, 0)
