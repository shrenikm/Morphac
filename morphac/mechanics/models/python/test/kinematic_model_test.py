import numpy as np
import pytest

from morphac.mechanics.models import KinematicModel


def test_invalid_construction():

    # KinematicModel is abstract and it should not be possible to construct
    # an object of this class.
    kinematic_model = KinematicModel("kinematic_model", 3, 2, 5)
