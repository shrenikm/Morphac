import numpy as np
import pytest

from morphac.constructs import ControlInput, State
from morphac.mechanics.models import TricycleModel
from morphac.robot.blueprint import Footprint


@pytest.fixture()
def generate_tricycle_model_list():

    t1 = TricycleModel(1, 2)
    t2 = TricycleModel(width=1.5, length=6.0)

    return t1, t2


def test_invalid_construction():

    # Width and length must both be positive.
    with pytest.raises(ValueError):
        _ = TricycleModel(0.0, 2.0)
    with pytest.raises(ValueError):
        _ = TricycleModel(2.0, 0.0)
    with pytest.raises(ValueError):
        _ = TricycleModel(-1.0, 2.0)
    with pytest.raises(ValueError):
        _ = TricycleModel(1.0, -2.0)


def test_width(generate_tricycle_model_list):

    t1, t2 = generate_tricycle_model_list

    assert t1.width == 1.0
    assert t2.width == 1.5

    # Make sure that width is read only.
    with pytest.raises(AttributeError):
        t1.width = 2.0
    with pytest.raises(AttributeError):
        t2.width = 3.0


def test_length(generate_tricycle_model_list):

    t1, t2 = generate_tricycle_model_list

    assert t1.length == 2.0
    assert t2.length == 6.0

    # Make sure that length is read only.
    with pytest.raises(AttributeError):
        t1.length = 4.0
    with pytest.raises(AttributeError):
        t2.length = 5.0


def test_size(generate_tricycle_model_list):

    t1, t2 = generate_tricycle_model_list

    # The sizes are fixed.
    assert t1.pose_size == 4
    assert t2.pose_size == 4

    assert t1.velocity_size == 0
    assert t2.velocity_size == 0

    assert t1.control_input_size == 2
    assert t2.control_input_size == 2

    # Make sure that these are read only.
    with pytest.raises(AttributeError):
        t1.pose_size = 2
    with pytest.raises(AttributeError):
        t2.velocity_size = 0
    with pytest.raises(AttributeError):
        t1.control_input_size = 3


def test_derivative_computation(generate_tricycle_model_list):

    t1, t2 = generate_tricycle_model_list

    # We only test that the function is called and returns properly, not the
    # actual computation as the cpp side tests this.

    # Test with positional arguments.
    der1 = t1.compute_state_derivative(
        robot_state=State([1, 2, 3, 4], []), control_input=ControlInput(2)
    )

    assert np.allclose(der1.data, [0, 0, 0, 0])

    # Making sure that the derivative can only be computed from control inputs
    # that are of the correct dimensions.
    with pytest.raises(ValueError):
        t1.compute_state_derivative(State(0, 4), ControlInput(2))
    with pytest.raises(ValueError):
        t1.compute_state_derivative(State(4, 1), ControlInput(2))
    with pytest.raises(ValueError):
        t2.compute_state_derivative(State(3, 0), ControlInput(2))
    with pytest.raises(ValueError):
        t2.compute_state_derivative(State(4, 0), ControlInput(3))


def test_normalize_state():

    tricycle_model = TricycleModel(1, 1)

    # As the cpp side tests the actual computation, we just check that the
    # normalize_state interface works.

    assert tricycle_model.normalize_state(robot_state=State(4, 0)) == State(4, 0)


def test_default_footprint(generate_tricycle_model_list):

    t1, _ = generate_tricycle_model_list

    # Just making sure that the default_footprint function returns a valid footprint.
    assert isinstance(t1.default_footprint(), Footprint)
