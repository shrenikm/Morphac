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

    ls1 = LineSpec(0., np.inf, 1.)
    ls2 = LineSpec(np.inf, 1., np.inf)
    ls3 = LineSpec(1., 0., 0.)
    ls4 = LineSpec(slope=-1., x_intercept=-1., y_intercept=1.)

    return ls1, ls2, ls3, ls4


def test_slope(generate_line_spec):

    ls1, ls2, ls3, ls4 = generate_line_spec

    assert ls1.slope == 0.
    assert ls2.slope == np.inf
    assert ls3.slope == 1.
    assert ls4.slope == -1.


def test_x_intercept(generate_line_spec):

    ls1, ls2, ls3, ls4 = generate_line_spec

    assert ls1.x_intercept == np.inf
    assert ls2.x_intercept == 1.
    assert ls3.x_intercept == 0.
    assert ls4.x_intercept == -1.


def test_slope(generate_line_spec):

    ls1, ls2, ls3, ls4 = generate_line_spec

    assert ls1.y_intercept == 1.
    assert ls2.y_intercept == np.inf
    assert ls3.y_intercept == 0.
    assert ls4.y_intercept == 1.


def test_equality(generate_line_spec):

    ls1, ls2, ls3, ls4 = generate_line_spec

    assert ls1 == LineSpec(0, np.inf, 1)
    assert ls2 == LineSpec(np.inf, 2 - 1, np.inf)
    assert ls3 == LineSpec(1, 2 - 2, 3 * 0)
    assert ls4 == LineSpec(slope=-1, x_intercept=-1, y_intercept=1)

    assert ls1 != ls2
    assert ls2 != ls3
    assert ls3 != ls4
    assert ls4 != ls1


# As the cpp test does all of the computation checking, we perform very basic
# tests here mainly to ensure that the bindings work.


def test_compute_line_spec(generate_line_spec):

    ls1, ls2, ls3, ls4 = generate_line_spec
