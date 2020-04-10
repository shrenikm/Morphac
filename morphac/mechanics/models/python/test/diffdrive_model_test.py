import numpy as np
import pytest

from morphac.constructs import State, ControlInput
from morphac.mechanics.models import DiffDriveModel


@pytest.fixture()
def generate_diffdrive_model_list():

    d1 = DiffDriveModel("d1", 1, 2)
    d2 = DiffDriveModel(name="d2", radius=1.5, length=6.)

    return d1, d2


def test_invalid_construction():

    # Radius and length must both be positive.
    with pytest.raises(ValueError):
        d3 = DiffDriveModel("d3", 0., 2.)
    with pytest.raises(ValueError):
        d4 = DiffDriveModel("d4", 2., 0.)
    with pytest.raises(ValueError):
        d5 = DiffDriveModel("d5", -1., 2.)
    with pytest.raises(ValueError):
        d6 = DiffDriveModel("d6", 1., -2.)


def test_name(generate_diffdrive_model_list):

    d1, d2 = generate_diffdrive_model_list

    assert d1.name == "d1"
    assert d2.name == "d2"


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
