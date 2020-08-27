import numpy as np
import pytest

from morphac.math.geometry import (
    create_arc,
    create_circular_polygon,
    create_rectangular_polygon,
    create_rounded_rectangular_polygon,
    create_triangular_polygon,
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


@pytest.fixture
def generate_triangular_polygon_list():
    t1 = create_triangular_polygon(2., 2., 0.)
    t2 = create_triangular_polygon(
        base=4.,
        height=6.,
        angle=np.pi / 3.,
        center=[-3., 2.],
    )

    return t1, t2


# As the cpp test does the numeric computation, here we only do some basic
# testing to ensure that the binding interface works correctly.

# Tests if the give set of points is be a structurally valid polygon.
def _is_valid_polygon(polygon):

    assert isinstance(polygon, np.ndarray)
    assert polygon.dtype == np.float64
    assert polygon.ndim == 2
    assert polygon.shape[1] == 2


def test_arc(generate_arc_list):

    a1, a2 = generate_arc_list

    _is_valid_polygon(a1)
    _is_valid_polygon(a2)


def test_invalid_arc():
    with pytest.raises(ValueError):
        _ = create_arc(0., np.pi / 3., -1., 0.1)
    with pytest.raises(ValueError):
        _ = create_arc(0., np.pi / 3., 1., 0.)


def test_circular_polygon(generate_circular_polygon_list):

    c1, c2 = generate_circular_polygon_list

    _is_valid_polygon(c1)
    _is_valid_polygon(c2)


def test_invalid_circular_polygon():
    with pytest.raises(ValueError):
        _ = create_circular_polygon(-1., 0.1)
    with pytest.raises(ValueError):
        _ = create_circular_polygon(1., 0.)


def test_rectangular_polygon(generate_rectangular_polygon_list):

    r1, r2 = generate_rectangular_polygon_list

    _is_valid_polygon(r1)
    _is_valid_polygon(r2)


def test_invalid_rectangular_polygon():
    with pytest.raises(ValueError):
        _ = create_rectangular_polygon(-2., 2., 0.)
    with pytest.raises(ValueError):
        _ = create_rectangular_polygon(2., -2., 0.)


def test_rounded_rectangular_polygon(
        generate_rounded_rectangular_polygon_list
):

    r1, r2 = generate_rounded_rectangular_polygon_list

    _is_valid_polygon(r1)
    _is_valid_polygon(r2)


def test_invalid_rounded_rectangular_polygon():
    with pytest.raises(ValueError):
        _ = create_rounded_rectangular_polygon(-2., 2., 0., 1., 0.1)
    with pytest.raises(ValueError):
        _ = create_rounded_rectangular_polygon(2., -2., 0., 1., 0.1)
    with pytest.raises(ValueError):
        _ = create_rounded_rectangular_polygon(2., 2., 0., -1., 0.1)
    with pytest.raises(ValueError):
        _ = create_rounded_rectangular_polygon(2., 2., 0., 1., 0.)


def test_triangular_polygon(generate_triangular_polygon_list):

    t1, t2 = generate_triangular_polygon_list

    _is_valid_polygon(t1)
    _is_valid_polygon(t2)


def test_invalid_triangular_polygon():
    with pytest.raises(ValueError):
        _ = create_triangular_polygon(-1., 2., 0.)
    with pytest.raises(ValueError):
        _ = create_triangular_polygon(1., -2., 0.)
