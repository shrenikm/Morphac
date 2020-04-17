import numpy as np
import pytest

from morphac.constructs import Input, State
from morphac.mechanics.models import TricycleModel


@pytest.fixture()
def generate_tricycle_model_list():

    t1 = TricycleModel(1, 2)
    t2 = TricycleModel(radius=1.5, length=6.)

    return t1, t2


def test_invalid_construction():

    # Radius and length must both be positive.
    with pytest.raises(ValueError):
        _ = TricycleModel(0., 2.)
    with pytest.raises(ValueError):
        _ = TricycleModel(2., 0.)
    with pytest.raises(ValueError):
        _ = TricycleModel(-1., 2.)
    with pytest.raises(ValueError):
        _ = TricycleModel(1., -2.)


def test_radius(generate_tricycle_model_list):

    t1, t2 = generate_tricycle_model_list

    assert t1.radius == 1.
    assert t2.radius == 1.5

    # Make sure that radius is read only.
    with pytest.raises(AttributeError):
        t1.radius = 2.
    with pytest.raises(AttributeError):
        t2.radius = 3.


def test_length(generate_tricycle_model_list):

    t1, t2 = generate_tricycle_model_list

    assert t1.length == 2.
    assert t2.length == 6.

    # Make sure that length is read only.
    with pytest.raises(AttributeError):
        t1.length = 4.
    with pytest.raises(AttributeError):
        t2.length = 5.


def test_size(generate_tricycle_model_list):

    t1, t2 = generate_tricycle_model_list

    # The sizes are fixed.
    assert t1.size_pose == 4
    assert t2.size_pose == 4

    assert t1.size_velocity == 0
    assert t2.size_velocity == 0

    assert t1.size_input == 2
    assert t2.size_input == 2

    # Make sure that these are read only.
    with pytest.raises(AttributeError):
        t1.size_pose = 2
    with pytest.raises(AttributeError):
        t2.size_velocity = 0
    with pytest.raises(AttributeError):
        t1.size_input = 3


def test_derivative_computation(generate_tricycle_model_list):

    t1, t2 = generate_tricycle_model_list

    # We only test that the function is called and returns properly, not the
    # actual computation as the cpp side tests this.
    der1 = t1.compute_state_derivative(State([1, 2, 3, 4], []), Input(2))

    assert np.allclose(der1.data, [0, 0, 0, 0])

    # Making sure that the derivative can only be computed from inputs that
    # are of the correct dimensions.
    with pytest.raises(ValueError):
        t1.compute_state_derivative(State(0, 4), Input(2))
    with pytest.raises(ValueError):
        t1.compute_state_derivative(State(4, 1), Input(2))
    with pytest.raises(ValueError):
        t2.compute_state_derivative(State(3, 0), Input(2))
    with pytest.raises(ValueError):
        t2.compute_state_derivative(State(4, 0), Input(3))
