import numpy as np
import pytest

from morphac.robot.blueprint import Footprint2D


@pytest.fixture()
def generate_footprint2D_list():

    f1 = Footprint2D([[1, 2]])
    f2 = Footprint2D(data=np.ones([10, 2]))

    return f1, f2


def test_invalid_construction():

    # Footprint data must be an nx2 matrix.
    with pytest.raises(ValueError):
        Footprint2D([1, 2])
    with pytest.raises(ValueError):
        Footprint2D([[1, 2, 3]])
    with pytest.raises(ValueError):
        Footprint2D(np.random.randn(10, 1))
    with pytest.raises(ValueError):
        Footprint2D(np.random.randn(10, 3))


def test_name(generate_footprint2D_list):

    f1, f2 = generate_footprint2D_list

    assert np.allclose(f1.data, [[1, 2]])
    assert np.allclose(f2.data, np.ones([10, 2]))

    # Making sure that the data is read only.
    with pytest.raises(AttributeError):
        f1.data = [[3, 4]]
    with pytest.raises(AttributeError):
        f1.data = [[1, 2]]
    with pytest.raises(AttributeError):
        f2.data = np.random.randn(5, 2)
    with pytest.raises(AttributeError):
        f2.data = np.ones([10, 2])
