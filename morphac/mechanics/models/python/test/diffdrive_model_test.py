import numpy as np
import pytest

from morphac.constructs import Input, State
from morphac.mechanics.models import DiffDriveModel


@pytest.fixture()
def generate_diffdrive_model_list():

    d1 = DiffDriveModel(1, 2)
    d2 = DiffDriveModel(radius=1.5, length=6.)

    return d1, d2


def test_invalid_construction():

    # Radius and length must both be positive.
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


def test_length(generate_diffdrive_model_list):

    d1, d2 = generate_diffdrive_model_list

    assert d1.length == 2.
    assert d2.length == 6.

    # Make sure that length is read only.
    with pytest.raises(AttributeError):
        d1.length = 4.
    with pytest.raises(AttributeError):
        d2.length = 5.


def test_size(generate_diffdrive_model_list):

    d1, d2 = generate_diffdrive_model_list

    # The sizes are fixed.
    assert d1.size_pose == 3
    assert d2.size_pose == 3

    assert d1.size_velocity == 0
    assert d2.size_velocity == 0

    assert d1.size_input == 2
    assert d2.size_input == 2

    # Make sure that these are read only.
    with pytest.raises(AttributeError):
        d1.size_pose = 2
    with pytest.raises(AttributeError):
        d2.size_velocity = 0
    with pytest.raises(AttributeError):
        d1.size_input = 3


def test_derivative_computation(generate_diffdrive_model_list):

    d1, d2 = generate_diffdrive_model_list

    # We only test that the function is called and returns properly, not the
    # actual computation as the cpp side tests this.
    der1 = d1.compute_state_derivative(State([1, 2, 3], []), Input(2))

    assert np.allclose(der1.data, [0, 0, 0])

    # Making sure that the derivative can only be computed from inputs that
    # are of the correct dimensions.
    with pytest.raises(ValueError):
        d1.compute_state_derivative(State(0, 3), Input(2))
    with pytest.raises(ValueError):
        d1.compute_state_derivative(State(3, 1), Input(2))
    with pytest.raises(ValueError):
        d2.compute_state_derivative(State(2, 0), Input(2))
    with pytest.raises(ValueError):
        d2.compute_state_derivative(State(3, 0), Input(3))
