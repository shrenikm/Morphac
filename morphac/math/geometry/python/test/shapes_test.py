import pytest

import numpy as np

from morphac.math.geometry import (
    ArcShape,
    CircleShape,
    RectangleShape,
    RoundedRectangleShape,
    TriangleShape,
)


@pytest.fixture()
def generate_shapes():

    arc = ArcShape(
        center=[-1.0, 2.0], start_angle=np.pi / 4, end_angle=np.pi / 2, radius=2.0
    )

    circle = CircleShape(center=[-1.0, 2.0], radius=2.0)

    rectangle = RectangleShape(
        center=[-1.0, 2.0], size_x=3.0, size_y=1.5, angle=np.pi / 4
    )

    rounded_rectangle = RoundedRectangleShape(
        center=[-1.0, 2.0], size_x=3.0, size_y=1.5, angle=np.pi / 4, radius=0.5
    )

    triangle = TriangleShape(center=[-1.0, 2.0], base=3.0, height=1.5, angle=np.pi / 4)

    return arc, circle, rectangle, rounded_rectangle, triangle


def test_arc_shape(generate_shapes):
    arc, _, _, _, _ = generate_shapes

    assert np.isclose(arc.start_angle, np.pi / 4)
    assert np.isclose(arc.end_angle, np.pi / 2)
    assert np.isclose(arc.radius, 2.0)
    assert np.allclose(arc.center, [-1, 2])


def test_invalid_arc_shape():
    # Invalid radius.
    with pytest.raises(ValueError):
        _ = ArcShape([0, 0], 0.0, np.pi / 2, -0.1)
    # Invalid start and end angles (equal).
    with pytest.raises(ValueError):
        _ = ArcShape([0, 0], np.pi / 2, np.pi / 2, 1.0)


def test_circle_shape(generate_shapes):
    _, circle, _, _, _ = generate_shapes

    assert np.isclose(circle.radius, 2.0)
    assert np.allclose(circle.center, [-1, 2])


def test_invalid_circle_shape():
    # Invalid radius.
    with pytest.raises(ValueError):
        _ = CircleShape([0, 0], -0.1)


def test_rectangle_shape(generate_shapes):
    _, _, rectangle, _, _ = generate_shapes

    assert np.isclose(rectangle.size_x, 3)
    assert np.isclose(rectangle.size_y, 1.5)
    assert np.isclose(rectangle.angle, np.pi / 4)
    assert np.allclose(rectangle.center, [-1, 2])


def test_invalid_rectangle_shape():
    # Invalid size_x.
    with pytest.raises(ValueError):
        _ = RectangleShape([0, 0], -0.1, 1.0, 0.0)
    # Invalid size_y.
    with pytest.raises(ValueError):
        _ = RectangleShape([0, 0], 1.0, -0.1, 0.0)


def test_rounded_rectangle_shape(generate_shapes):
    _, _, _, rounded_rectangle, _ = generate_shapes

    assert np.isclose(rounded_rectangle.size_x, 3)
    assert np.isclose(rounded_rectangle.size_y, 1.5)
    assert np.isclose(rounded_rectangle.angle, np.pi / 4)
    assert np.isclose(rounded_rectangle.radius, 0.5)
    assert np.allclose(rounded_rectangle.center, [-1, 2])


def test_invalid_rounded_rectangle_shape():
    # Invalid size_x.
    with pytest.raises(ValueError):
        _ = RoundedRectangleShape([0, 0], -0.1, 1.0, 0.0, 0.1)
    # Invalid size_y.
    with pytest.raises(ValueError):
        _ = RoundedRectangleShape([0, 0], 1.0, -0.1, 0.0, 0.1)
    # Invalid radius.
    with pytest.raises(ValueError):
        _ = RoundedRectangleShape([0, 0], 1.0, 1.0, 0.0, -0.1)
    # The radius must also be smaller than half of the sizes.
    with pytest.raises(ValueError):
        _ = RoundedRectangleShape([0, 0], 3.0, 2.0, 0.0, 1.1)
    with pytest.raises(ValueError):
        _ = RoundedRectangleShape([0, 0], 2.0, 3.0, 0.0, 1.1)


def test_triangle_shape(generate_shapes):
    _, _, _, _, triangle_shape = generate_shapes

    assert np.isclose(triangle_shape.base, 3)
    assert np.isclose(triangle_shape.height, 1.5)
    assert np.isclose(triangle_shape.angle, np.pi / 4)
    assert np.allclose(triangle_shape.center, [-1, 2])


def test_invalid_triangle_shape():
    # Invalid base.
    with pytest.raises(ValueError):
        _ = TriangleShape([0, 0], -0.1, 1.0, 0.0)
    # Invalid height.
    with pytest.raises(ValueError):
        _ = TriangleShape([0, 0], 1.0, -0.1, 0.0)
