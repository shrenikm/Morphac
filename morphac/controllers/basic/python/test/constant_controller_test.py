import numpy as np
import pytest

from morphac.controllers.basic import ConstantController
from morphac.utils.pytest_utils import set_standard_testing_random_seed


@pytest.fixture()
def generate_controller_list():
    c1 = ConstantController([0])
    set_standard_testing_random_seed()
    c2 = ConstantController(np.random.randn(6))

    return c1, c2


def test_invalid_construction():

    with pytest.raises(ValueError):
        _ = ConstantController([])


def test_compute(generate_controller_list):

    c1, c2 = generate_controller_list

    set_standard_testing_random_seed()
    data = np.random.randn(6)

    assert np.allclose(c1.compute().data, [0])
    assert np.allclose(c2.compute().data, data)
