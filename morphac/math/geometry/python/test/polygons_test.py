import numpy as np
import pytest

from morphac.math.geometry import (
    ArcShape,
    CircleShape,
    RectangleShape,
    RoundedRectangleShape,
    TriangleShape,
    create_arc,
    create_circular_polygon,
    create_rectangular_polygon,
    create_rounded_rectangular_polygon,
    create_triangular_polygon,
    compute_bounding_box,
    is_point_inside_bounding_box,
)


@pytest.fixture
def generate_arc_list():
    arc1 = create_arc(ArcShape(0.0, np.pi / 3.0, 1.5), 0.01)
    arc2 = create_arc(
        ArcShape(
            start_angle=-np.pi, end_angle=-np.pi / 2, radius=1.0, center=[-4.0, 4.0],
        ),
        angular_resolution=0.1,
    )

    return arc1, arc2


@pytest.fixture
def generate_circular_polygon_list():
    c1 = create_circular_polygon(CircleShape(1.5), 0.01)
    c2 = create_circular_polygon(
        CircleShape(radius=1.0, center=[-4.0, 4.0]), angular_resolution=0.1
    )

    return c1, c2


@pytest.fixture
def generate_rectangular_polygon_list():
    r1 = create_rectangular_polygon(RectangleShape(6.0, 4.0, 0.0))
    r2 = create_rectangular_polygon(
        RectangleShape(size_x=6.0, size_y=4.0, angle=np.pi / 3.0, center=[-4.0, 4.0])
    )

    return r1, r2


@pytest.fixture
def generate_rounded_rectangular_polygon_list():
    r1 = create_rounded_rectangular_polygon(
        RoundedRectangleShape(6.0, 4.0, 0.0, 1.5), 0.01
    )
    r2 = create_rounded_rectangular_polygon(
        RoundedRectangleShape(
            size_x=6.0, size_y=4.0, angle=np.pi / 3.0, radius=1.0, center=[-4.0, 4.0]
        ),
        angular_resolution=0.1,
    )

    return r1, r2


@pytest.fixture
def generate_triangular_polygon_list():
    t1 = create_triangular_polygon(TriangleShape(2.0, 2.0, 0.0))
    t2 = create_triangular_polygon(
        TriangleShape(base=4.0, height=6.0, angle=np.pi / 3.0, center=[-3.0, 2.0])
    )

    return t1, t2


# As the cpp test does the numeric computation, here we only do some basic
# testing to ensure that the binding interface works correctly.
# Also note that as the shapes test covers invalid construction, we only test
# for invalid resolutions.

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
        _ = create_arc(ArcShape(0.0, np.pi / 3.0, 1.0), 0.0)


def test_circular_polygon(generate_circular_polygon_list):

    c1, c2 = generate_circular_polygon_list

    _is_valid_polygon(c1)
    _is_valid_polygon(c2)


def test_invalid_circular_polygon():
    with pytest.raises(ValueError):
        _ = create_circular_polygon(CircleShape(1.0), 0.0)


def test_rectangular_polygon(generate_rectangular_polygon_list):

    r1, r2 = generate_rectangular_polygon_list

    _is_valid_polygon(r1)
    _is_valid_polygon(r2)


def test_rounded_rectangular_polygon(generate_rounded_rectangular_polygon_list):

    r1, r2 = generate_rounded_rectangular_polygon_list

    _is_valid_polygon(r1)
    _is_valid_polygon(r2)


def test_invalid_rounded_rectangular_polygon():
    with pytest.raises(ValueError):
        _ = create_rounded_rectangular_polygon(
            RoundedRectangleShape(2.0, 2.0, 0.0, 1.0), 0.0
        )


def test_triangular_polygon(generate_triangular_polygon_list):

    t1, t2 = generate_triangular_polygon_list

    _is_valid_polygon(t1)
    _is_valid_polygon(t2)


def test_compute_bounding_box():
    # The cpp test tests this thoroughly, so we have a simple test here for the interface.
    polygon = [[-2.0, 0.0], [0.0, 3.0], [2.0, 0.0], [0.0, -3.0]]

    bounding_box = compute_bounding_box(polygon=polygon)

    expected_bounding_box = [[-2.0, 3.0], [2.0, 3.0], [2.0, -3.0], [-2.0, -3.0]]

    assert np.allclose(bounding_box, expected_bounding_box)


def test_is_point_inside_bounding_box():

    bounding_box = [[-2, 4], [2, 4], [2, -4], [-2, -4]]

    # Running some basic tests.
    assert is_point_inside_bounding_box([0, 0], bounding_box)
    assert is_point_inside_bounding_box([-2, -4], bounding_box)
    assert is_point_inside_bounding_box([2, 4], bounding_box)

    assert not is_point_inside_bounding_box([10, 10], bounding_box)
    assert not is_point_inside_bounding_box([-3, 0], bounding_box)
    assert not is_point_inside_bounding_box([3, 0], bounding_box)
    assert not is_point_inside_bounding_box([0, -5], bounding_box)
    assert not is_point_inside_bounding_box([0, 5], bounding_box)

