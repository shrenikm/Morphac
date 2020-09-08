import pytest

import numpy as np

from morphac.math.geometry import (
    LineSpec,
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


def test_slope(generate_line_spec):

    ls1, ls2, ls3, ls4 = generate_line_spec

    assert ls1.slope == 0.0
    assert ls2.slope == np.inf
    assert ls3.slope == 1.0
    assert ls4.slope == -1.0


def test_x_intercept(generate_line_spec):

    ls1, ls2, ls3, ls4 = generate_line_spec

    assert ls1.x_intercept == np.inf
    assert ls2.x_intercept == 1.0
    assert ls3.x_intercept == 0.0
    assert ls4.x_intercept == 1.0


def test_slope(generate_line_spec):

    ls1, ls2, ls3, ls4 = generate_line_spec

    assert ls1.y_intercept == 1.0
    assert ls2.y_intercept == np.inf
    assert ls3.y_intercept == 0.0
    assert ls4.y_intercept == 1.0


def test_equality(generate_line_spec):

    ls1, ls2, ls3, ls4 = generate_line_spec

    assert ls1 == LineSpec(0, np.inf, 1)
    assert ls2 == LineSpec(np.inf, 2 - 1, np.inf)
    assert ls3 == LineSpec(1, 2 - 2, 3 * 0)
    assert ls4 == LineSpec(slope=-1, x_intercept=1, y_intercept=1)

    assert ls1 != ls2
    assert ls2 != ls3
    assert ls3 != ls4
    assert ls4 != ls1


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

    _, _, ls3, ls4 = generate_line_spec

    assert are_lines_parallel([0.0, 0.0], [1.0, 0.0], [-2.0, 5.0], [3.0, 5.0])
    assert are_lines_parallel(
        start_point1=[0.0, 0.0],
        end_point1=[0.0, 1.0],
        start_point2=[5.0, -2.0],
        end_point2=[5.0, 3.0],
    )
    assert are_lines_parallel(compute_line_spec([0.0, 0.0], [1.0, 1.0]), ls3)
    assert are_lines_parallel(
        line_spec1=compute_line_spec([0.0, 0.0], [1.0, -1.0]), line_spec2=ls4
    )


def test_are_lines_perpendicular(generate_line_spec):

    _, _, ls3, ls4 = generate_line_spec

    assert are_lines_perpendicular([0.0, 0.0], [0.0, 1.0], [-2.0, 5.0], [3.0, 5.0])
    assert are_lines_perpendicular(
        start_point1=[0.0, 0.0],
        end_point1=[1.0, 0.0],
        start_point2=[5.0, -2.0],
        end_point2=[5.0, 3.0],
    )
    assert are_lines_perpendicular(compute_line_spec([0.0, 0.0], [1.0, 1.0]), ls4)
    assert are_lines_perpendicular(
        line_spec1=compute_line_spec([0.0, 0.0], [1.0, -1.0]), line_spec2=ls3
    )
