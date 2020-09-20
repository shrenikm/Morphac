import numpy as np
import pytest

from morphac.controllers.basic import ZeroController


@pytest.fixture()
def generate_controller_list():
    c1 = ZeroController(1)
    c2 = ZeroController(6)

    return c1, c2


def test_invalid_construction():

    with pytest.raises(ValueError):
        _ = ZeroController(-1)
    with pytest.raises(ValueError):
        _ = ZeroController(0)


def test_compute(generate_controller_list):

    c1, c2 = generate_controller_list

    assert np.allclose(c1.compute().data, [0])
    assert np.allclose(c2.compute().data, np.zeros(6))
