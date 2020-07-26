import numpy as np
import pytest

from morphac.constructs import State, Trajectory


@pytest.fixture()
def generate_trajectory_list():
    # List of trajectories constructed in different ways.
    t1 = Trajectory(knot_point=State(2, 2))
    t2 = Trajectory(
        knot_points=[State([1, 1], [1]),
                     State([2, 2], [2]),
                     State([3, 3], [3])])
    np.random.seed(7)
    t3 = Trajectory(data=np.random.randn(100, 5), pose_size=3, velocity_size=2)

    return t1, t2, t3


def test_invalid_construction():

    with pytest.raises(ValueError):
        _ = Trajectory(State(0, 0))
    with pytest.raises(ValueError):
        _ = Trajectory([])
    with pytest.raises(ValueError):
        _ = Trajectory([State(3, 2), State(2, 2)])
    with pytest.raises(ValueError):
        _ = Trajectory(np.empty([0, 0]))
    with pytest.raises(ValueError):
        _ = Trajectory(np.zeros([100, 2]), 1, 0)


def test_dim(generate_trajectory_list):

    t1, t2, t3 = generate_trajectory_list

    assert t1.dim == 4
    assert t2.dim == 3
    assert t3.dim == 5

    # Making sure that the dim is read only.
    with pytest.raises(AttributeError):
        t1.dim = 3
    with pytest.raises(AttributeError):
        t2.dim = 2
    with pytest.raises(AttributeError):
        t3.dim = 5


def test_size(generate_trajectory_list):

    t1, t2, t3 = generate_trajectory_list

    assert t1.size == 1
    assert t2.size == 3
    assert t3.size == 100

    # Making sure that the size is read only.
    with pytest.raises(AttributeError):
        t1.size = 2
    with pytest.raises(AttributeError):
        t2.size = 4
    with pytest.raises(AttributeError):
        t3.size = 100


def test_pose_size(generate_trajectory_list):

    t1, t2, t3, = generate_trajectory_list

    assert t1.pose_size == 2
    assert t2.pose_size == 2
    assert t3.pose_size == 3

    # Making sure that the size is read only.
    with pytest.raises(AttributeError):
        t1.pose_size = 1
    with pytest.raises(AttributeError):
        t2.pose_size = 3
    with pytest.raises(AttributeError):
        t3.pose_size = 3


def test_velocity_size(generate_trajectory_list):

    t1, t2, t3, = generate_trajectory_list

    assert t1.velocity_size == 2
    assert t2.velocity_size == 1
    assert t3.velocity_size == 2

    # Making sure that the size is read only.
    with pytest.raises(AttributeError):
        t1.velocity_size = 1
    with pytest.raises(AttributeError):
        t2.velocity_size = 2
    with pytest.raises(AttributeError):
        t3.velocity_size = 2


def test_data(generate_trajectory_list):

    t1, t2, t3 = generate_trajectory_list

    # Test getting data.
    # Data for t3
    np.random.seed(7)
    data3 = np.random.randn(100, 5)

    assert np.allclose(t1.data, [0, 0, 0, 0])
    assert np.allclose(t2.data, [[1, 1, 1], [2, 2, 2], [3, 3, 3]])
    assert np.allclose(t3.data, data3)

    # Test setting data.
    t1.data = [[1, 2, 3, 4]]
    t2.data = np.ones([3, 3])
    np.random.seed(0)
    data3 = np.random.randn(100, 5)
    t3.data = data3

    assert np.allclose(t1.data, [1, 2, 3, 4])
    assert np.allclose(t2.data, [[1, 1, 1], [1, 1, 1], [1, 1, 1]])
    assert np.allclose(t3.data, data3)

    # test invalid set data.
    with pytest.raises(ValueError):
        t1.data = [[1, 2, 3]]
    with pytest.raises(ValueError):
        t2.data = np.zeros([4, 4])
    with pytest.raises(ValueError):
        t3.data = np.zeros([100, 4])


def test_getitem(generate_trajectory_list):

    t1, t2, t3 = generate_trajectory_list

    for t in [t1, t2, t3]:
        for i in range(t.size):
            assert t[i] == State(t.data[i, :t.pose_size],
                                 t.data[i, t.pose_size:])
            # Test negative indexing.
            assert t[-(t.size - i)] == State(t.data[i, :t.pose_size],
                                             t.data[i, t.pose_size:])

    # Test invalid getitem
    with pytest.raises(IndexError):
        _ = t1[-2]
    with pytest.raises(IndexError):
        _ = t2[3]
    with pytest.raises(IndexError):
        _ = t3[200]


def test_setitem(generate_trajectory_list):

    t1, t2, t3 = generate_trajectory_list

    t1[0] = State([1, 1], [1, 1])
    t2[1] = State([1, 1], [1])
    np.random.seed(0)
    data3 = np.random.randn(100, 5)
    for i in range(100):
        t3[i] = State(data3[i, :3], data3[i, 3:])

    assert np.allclose(t1.data, [1, 1, 1, 1])
    assert np.allclose(t2.data, [[1, 1, 1], [1, 1, 1], [3, 3, 3]])
    assert np.allclose(t3.data, data3)

    # Test invalid setitem
    with pytest.raises(IndexError):
        t1[-2] = State(2, 2)
    with pytest.raises(IndexError):
        t2[-4] = State(2, 1)
    with pytest.raises(IndexError):
        t3[100] = State(3, 2)

    # Note that this check for invalid state setting is only applicable for
    # the python binding. In cpp, this is done through the [] operator that
    # returns a reference and thus no state validation can take place.
    with pytest.raises(ValueError):
        t1[0] = State(0, 0)
    with pytest.raises(ValueError):
        t2[0] = State(2, 2)
    with pytest.raises(ValueError):
        t3[0] = State(2, 2)


def test_addition(generate_trajectory_list):

    t1, t2, t3 = generate_trajectory_list

    t1 += Trajectory(State([1, 1], [1, 1]))

    assert t1.size == 2
    assert np.allclose(t1.data, [[0, 0, 0, 0], [1, 1, 1, 1]])

    t2 += t2

    assert t2.size == 6
    assert np.allclose(t2.data, [[1, 1, 1], [2, 2, 2], [
                       3, 3, 3], [1, 1, 1], [2, 2, 2], [3, 3, 3]])

    np.random.seed(0)
    data3 = np.random.randn(200, 5)
    t4 = t3 + Trajectory(data3, 3, 2)

    # Make sure that t3 is unchanged.
    assert t3.size == 100

    assert t4.size == 300
    assert np.allclose(t4.data, np.vstack([t3.data, data3]))

    # Test invalid addition.
    with pytest.raises(ValueError):
        t1 += t2
    with pytest.raises(ValueError):
        t2 += t3
    with pytest.raises(ValueError):
        t3 += t1
    with pytest.raises(ValueError):
        t1 += Trajectory(State(0, 0))
    with pytest.raises(ValueError):
        t2 += Trajectory(State(2, 2))
    with pytest.raises(ValueError):
        t2 += Trajectory(State(2, 2))


def test_equality(generate_trajectory_list):

    t1, t2, t3 = generate_trajectory_list

    assert t1 == t1
    assert t2 == t2
    assert t3 == t3

    assert t1 == Trajectory(State(2, 2))
    assert t2 == Trajectory([[1, 1, 1], [2, 2, 2], [3, 3, 3]], 2, 1)

    assert t1 != t2
    assert t2 != t3
    assert t3 != t1

    assert t1 != Trajectory(State(2, 1))
    assert t1 != Trajectory(State(1, 2))
    assert t2 != Trajectory([[1, 1, 1], [2, 2, 2], [3, 3, 3]], 1, 2)


def test_repr(generate_trajectory_list):

    for t in generate_trajectory_list:
        assert isinstance(repr(t), str)


def test_add_knot_point(generate_trajectory_list):

    t1, t2, t3 = generate_trajectory_list

    t1.add_knot_point(State([1, 1], [1, 1]), 0)
    t2.add_knot_point(State([1.5, 1.5], [1.5]), 1)
    # Test the overload without an index.
    np.random.seed(7)
    data3 = np.random.randn(100, 5)
    t3.add_knot_point(State(3, 2))

    assert np.allclose(t1.data, [[1, 1, 1, 1], [0, 0, 0, 0]])
    assert np.allclose(
        t2.data, [[1, 1, 1], [1.5, 1.5, 1.5], [2, 2, 2], [3, 3, 3]])
    assert np.allclose(t3.data, np.vstack([data3, [0]*5]))

    # Test invalid add_knot_point.
    # Note that the size of each trajectory has now increased by one.

    # Invalid states.
    with pytest.raises(ValueError):
        t1.add_knot_point(State(2, 1), 0)
    with pytest.raises(ValueError):
        t2.add_knot_point(State(3, 1), 0)
    with pytest.raises(ValueError):
        t3.add_knot_point(State(2, 3), 0)

    # Invalid indices.
    with pytest.raises(IndexError):
        t1.add_knot_point(State(2, 2), -1)
    with pytest.raises(IndexError):
        t2.add_knot_point(State(2, 1), 5)
    with pytest.raises(IndexError):
        t3.add_knot_point(State(3, 2), 200)


def test_add_knot_points(generate_trajectory_list):

    t1, t2, t3 = generate_trajectory_list

    # Making copies as the values of the trajectories might change while
    # catching exceptions caused by add_knot_point.

    t1.add_knot_points([State(2, 2), State(2, 2)], [1, 2])
    t2.add_knot_points([State(2, 1), State(2, 1), State(2, 1)], [0, 2, 5])
    t3.add_knot_points([State(3, 2), State(3, 2)], [0, 101])

    assert np.allclose(t1.data, [[0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0]])
    assert np.allclose(
        t2.data, [[0, 0, 0],
                  [1, 1, 1],
                  [0, 0, 0],
                  [2, 2, 2],
                  [3, 3, 3],
                  [0, 0, 0]])
    assert t3[0] == State(3, 2)
    assert t3[-1] == State(3, 2)

# Separate invalid test functions as these may modify the trajectory depending
# on which index the invalidity is present at.


def test_invalid_add_knot_points_due_to_sizes(generate_trajectory_list):

    t1, t2, t3 = generate_trajectory_list

    # Invalid add knot points.

    # Invalid points and indices sizes.
    with pytest.raises(ValueError):
        t1.add_knot_points([State(2, 2), State(2, 2)], [0, 1, 2])
    with pytest.raises(ValueError):
        t2.add_knot_points([State(2, 1), State(2, 1)], [0])

    # Invalid state sizes.
    with pytest.raises(ValueError):
        t1.add_knot_points([State(2, 3), State(2, 2)], [1, 2])
    with pytest.raises(ValueError):
        t2.add_knot_points([State(2, 1), State(2, 1), State(1, 1)], [0, 2, 5])
    with pytest.raises(ValueError):
        t3.add_knot_points([State(3, 2), State(2, 3)], [0, 101])


def test_invalid_add_knot_points_due_to_indices(generate_trajectory_list):

    t1, t2, t3 = generate_trajectory_list

    # Invalid indices.
    # We do not allow for negative indexing here.
    # Also the sizes have changed from the previous add_knot_points calls.
    with pytest.raises(IndexError):
        t1.add_knot_points([State(2, 2), State(2, 2)], [-1, 2])
    with pytest.raises(IndexError):
        t2.add_knot_points([State(2, 1), State(2, 1), State(2, 1)], [0, 2, 6])
    with pytest.raises(IndexError):
        t3.add_knot_points(
            [State(3, 2), State(3, 2), State(3, 2)], [0, 50, 103])
