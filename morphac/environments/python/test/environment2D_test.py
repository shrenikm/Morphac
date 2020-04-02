import numpy as np
import pytest

from morphac.environments import Environment2D


@pytest.fixture()
def generate_environment2D_list():

    # List of environments constructed in different ways.
    # Also tests initialization

    e1 = Environment2D(width=2, height=2, resolution=1)
    e2 = Environment2D([[1, 2], [3, 4], [5, 6]], 0.5)
    e3 = Environment2D(((0, 1, 0), (2, -1, 0)), 0.1)
    e4 = Environment2D(data=np.eye(100), resolution=10)

    return e1, e2, e3, e4


def test_size(generate_environment2D_list):

    e1, e2, e3, e4 = generate_environment2D_list

    assert e1.width == 2
    assert e1.height == 2
