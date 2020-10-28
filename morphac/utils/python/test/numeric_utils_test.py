from morphac.utils.numeric_utils import is_equal

# The actual rigorous numerical testing happens on the cpp side. Here we run
# some basic sanity tests.


def test_is_equal():

    assert is_equal(value1=1.5, value2=1.5)
    assert not is_equal(value1=7.0, value2=7.001)

    # Really small values.
    assert is_equal(1e-16 + 2.5e-16, 3.5e-16)
    assert not is_equal(1e-16, 1e-15, 1e-16)

    # Large values.
    assert is_equal(9e16 - 2e16, 7e16)
    assert not is_equal(9e16 - 2e16, 7.001e16)

    # Test with tolerances.
    assert is_equal(value1=7.0, value2=7.001, absolute_tolerance=1e-2)
    assert is_equal(value1=7.0, value2=7.001, relative_tolerance=1e-2)
    assert not is_equal(value1=7.0, value2=7.001, absolute_tolerance=1e-4)
    assert not is_equal(value1=7.0, value2=7.001, relative_tolerance=1e-4)
