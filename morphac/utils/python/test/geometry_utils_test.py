import numpy as np
import pytest

from morphac.utils import (
    create_arc,
    create_circular_polygon,
    create_rectangular_polygon,
    create_rounded_rectangular_polygon,
)


@pytest.fixture
def generate_arc_list():
    arc1 = create_arc(0., np.pi / 3., 1.5, 0.01)
    arc2 = create_arc(
        start_angle=-np.pi,
        end_angle=-np.pi / 2,
        radius=1.,
        angular_resolution=0.1,
        center=[-4., 4.]
    )

    return arc1, arc2


@pytest.fixture
def generate_circular_polygon_list():
    c1 = create_circular_polygon(1.5, 0.01)
    c2 = create_circular_polygon(
        radius=1.,
        angular_resolution=0.1,
        center=[-4., 4.]
    )

    return c1, c2


@pytest.fixture
def generate_rectangular_polygon_list():
    r1 = create_rectangular_polygon(6., 4., 0.)
    r2 = create_rectangular_polygon(
        size_x=6.,
        size_y=4.,
        angle=np.pi / 3.,
        center=[-4., 4.]
    )

    return r1, r2


@pytest.fixture
def generate_rounded_rectangular_polygon_list():
    r1 = create_rounded_rectangular_polygon(6., 4., 0., 1.5, 0.01)
    r2 = create_rounded_rectangular_polygon(
        size_x=6.,
        size_y=4.,
        angle=np.pi / 3.,
        radius=1.,
        angular_resolution=0.1,
        center=[-4., 4.]
    )

    return r1, r2


# As the cpp test does the numeric computation, here we only do some basic
# testing to ensure that the binding interface works correctly.

def test_arc(generate_arc_list):

    a1, a2 = generate_arc_list

    assert isinstance(a1, np.ndarray)
    assert isinstance(a2, np.ndarray)

    assert a1.ndim == 2
    assert a2.ndim == 2

    assert a1.shape[1] == 2
    assert a2.shape[1] == 2


def test_invalid_arc():
    with pytest.raises(ValueError):
        _ = create_arc(0., np.pi / 3., -1., 0.1)
    with pytest.raises(ValueError):
        _ = create_arc(0., np.pi / 3., 1., 0.)


def test_circular_polygon(generate_circular_polygon_list):

    c1, c2 = generate_circular_polygon_list

    assert isinstance(c1, np.ndarray)
    assert isinstance(c2, np.ndarray)

    assert c1.ndim == 2
    assert c2.ndim == 2

    assert c1.shape[1] == 2
    assert c2.shape[1] == 2


def test_invalid_circular_polygon():
    with pytest.raises(ValueError):
        _ = create_circular_polygon(-1., 0.1)
    with pytest.raises(ValueError):
        _ = create_circular_polygon(1., 0.)


def test_rectangular_polygon(generate_rectangular_polygon_list):

    r1, r2 = generate_rectangular_polygon_list

    assert isinstance(r1, np.ndarray)
    assert isinstance(r2, np.ndarray)

    assert r1.ndim == 2
    assert r2.ndim == 2

    assert r1.shape[1] == 2
    assert r2.shape[1] == 2


def test_invalid_rectangular_polygon():
    with pytest.raises(ValueError):
        _ = create_rectangular_polygon(-2., 2., 0.)
    with pytest.raises(ValueError):
        _ = create_rectangular_polygon(2., -2., 0.)


def test_rounded_rectangular_polygon(
        generate_rounded_rectangular_polygon_list
):

    r1, r2 = generate_rounded_rectangular_polygon_list

    assert isinstance(r1, np.ndarray)
    assert isinstance(r2, np.ndarray)

    assert r1.ndim == 2
    assert r2.ndim == 2

    assert r1.shape[1] == 2
    assert r2.shape[1] == 2


def test_invalid_rounded_rectangular_polygon():
    with pytest.raises(ValueError):
        _ = create_rounded_rectangular_polygon(-2., 2., 0., 1., 0.1)
    with pytest.raises(ValueError):
        _ = create_rounded_rectangular_polygon(2., -2., 0., 1., 0.1)
    with pytest.raises(ValueError):
        _ = create_rounded_rectangular_polygon(2., 2., 0., -1., 0.1)
    with pytest.raises(ValueError):
        _ = create_rounded_rectangular_polygon(2., 2., 0., 1., 0.)
