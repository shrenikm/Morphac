import pytest

import numpy as np

from morphac.math.geometry import (
    LineSpec,
    PointProjection,
    compute_line_spec,
    are_lines_parallel,
    are_lines_perpendicular,
)


@pytest.fixture()
def generate_line_spec():

    ls1 = LineSpec(0.0, np.inf, 1.0)
    ls2 = LineSpec(np.inf, 1.0, np.inf)
    ls3 = LineSpec(1.0, 0.0, 0.0)
    ls4 = LineSpec(slope=-1.0, x_intercept=1.0, y_intercept=1.0)

    return ls1, ls2, ls3, ls4


@pytest.fixture()
def generate_point_projection():

    pp1 = PointProjection(0.0, 0.0, [0.0, 0.0])
    pp2 = PointProjection(distance=1.0, alpha=np.inf, projection=[1.0, 1.0])
    pp3 = PointProjection(distance=10.0, projection=[-1.0, -1.0])

    return pp1, pp2, pp3


def test_line_spec(generate_line_spec):

    ls1, ls2, ls3, ls4 = generate_line_spec

    # Slope.
    assert ls1.slope == 0.0
    assert ls2.slope == np.inf
    assert ls3.slope == 1.0
    assert ls4.slope == -1.0

    # X intercept.
    assert ls1.x_intercept == np.inf
    assert ls2.x_intercept == 1.0
    assert ls3.x_intercept == 0.0
    assert ls4.x_intercept == 1.0

    # Y intercept.
    assert ls1.y_intercept == 1.0
    assert ls2.y_intercept == np.inf
    assert ls3.y_intercept == 0.0
    assert ls4.y_intercept == 1.0


def test_line_spec_equality(generate_line_spec):

    ls1, ls2, ls3, ls4 = generate_line_spec

    assert ls1 == LineSpec(0, np.inf, 1)
    assert ls2 == LineSpec(np.inf, 2 - 1, np.inf)
    assert ls3 == LineSpec(1, 2 - 2, 3 * 0)
    assert ls4 == LineSpec(slope=-1, x_intercept=1, y_intercept=1)

    assert ls1 != ls2
    assert ls2 != ls3
    assert ls3 != ls4
    assert ls4 != ls1


def test_invalid_line_spec():

    with pytest.raises(ValueError):
        _ = LineSpec(0, np.inf, np.inf)
    with pytest.raises(ValueError):
        _ = LineSpec(1.0, np.inf, 0.0)
    with pytest.raises(ValueError):
        _ = LineSpec(np.inf, np.inf, 0.0)
    with pytest.raises(ValueError):
        _ = LineSpec(0.0, 0.0, np.inf)
    with pytest.raises(ValueError):
        _ = LineSpec(1.0, 0.0, np.inf)


def test_point_projection(generate_point_projection):
    pp1, pp2, pp3 = generate_point_projection

    # Distance.
    assert pp1.distance == 0.0
    assert pp2.distance == 1.0
    assert pp3.distance == 10.0

    # Alpha.
    assert pp1.alpha == 0.0
    assert pp2.alpha == np.inf
    assert pp3.alpha == np.inf

    # Projection.
    assert np.allclose(pp1.projection, [0.0, 0.0])
    assert np.allclose(pp2.projection, [1.0, 1.0])
    assert np.allclose(pp3.projection, [-1.0, -1.0])


def test_invalid_point_projection():

    with pytest.raises(ValueError):
        _ = PointProjection(-0.1, 0.0, [0.0, 0.0])
    with pytest.raises(ValueError):
        _ = PointProjection(-0.1, [0.0, 0.0])


# As the cpp test does all of the computation checking, we perform very basic
# tests here mainly to ensure that the bindings work.


def test_compute_line_spec(generate_line_spec):

    ls1, ls2, ls3, ls4 = generate_line_spec

    assert ls1 == compute_line_spec([-2.0, 1.0], [2.0, 1.0])
    assert ls2 == compute_line_spec([1.0, -2.0], [1.0, 2.0])
    assert ls3 == compute_line_spec((-2.0, -2.0), (2.0, 2.0))
    assert ls4 == compute_line_spec(
        start_point=np.array([-1.0, 2.0]), end_point=np.array([3.0, -2.0])
    )


def test_are_lines_parallel(generate_line_spec):

    _, _, ls3, _ = generate_line_spec

    assert are_lines_parallel([0.0, 0.0], [1.0, 0.0], [-2.0, 5.0], [3.0, 5.0])
    assert are_lines_parallel(
        start_point1=[0.0, 0.0],
        end_point1=[0.0, 1.0],
        start_point2=[5.0, -2.0],
        end_point2=[5.0, 3.0],
    )
    assert are_lines_parallel(compute_line_spec([0.0, 0.0], [1.0, 1.0]), ls3)
    # Testing with in place construction.
    assert are_lines_parallel(
        line_spec1=compute_line_spec([0.0, 0.0], [1.0, -1.0]),
        line_spec2=LineSpec(-1.0, 1.0, 1.0),
    )


def test_are_lines_perpendicular(generate_line_spec):

    _, _, _, ls4 = generate_line_spec

    assert are_lines_perpendicular([0.0, 0.0], [0.0, 1.0], [-2.0, 5.0], [3.0, 5.0])
    assert are_lines_perpendicular(
        start_point1=[0.0, 0.0],
        end_point1=[1.0, 0.0],
        start_point2=[5.0, -2.0],
        end_point2=[5.0, 3.0],
    )
    assert are_lines_perpendicular(compute_line_spec([0.0, 0.0], [1.0, 1.0]), ls4)
    # Testing with in place construction.
    assert are_lines_perpendicular(
        line_spec1=compute_line_spec([0.0, 0.0], [1.0, -1.0]),
        line_spec2=LineSpec(1.0, 0.0, 0.0),
    )
