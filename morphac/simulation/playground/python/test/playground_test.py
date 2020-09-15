import numpy as np
import pytest

from morphac.constructs import ControlInput, State
from morphac.environment import Map
from morphac.mechanics.models import DiffdriveModel
from morphac.math.numeric import (
    IntegratorType,
    Integrator,
    MidPointIntegrator,
    RK4Integrator,
)
from morphac.robot.pilot import Pilot
from morphac.robot.blueprint import Footprint, Robot
from morphac.simulation.playground import Playground
from morphac.simulation.playground import PlaygroundSpec


# Custom derived Pilot class to be used for testing.
class CustomPilot(Pilot):
    def __init__(self, control_input_data):

        Pilot.__init__(self)
        self.control_input_data = control_input_data

    def execute(self, playground_state, uid):

        return ControlInput(self.control_input_data)


@pytest.fixture()
def generate_playground():
    playground_spec = PlaygroundSpec("playground", 0.01)
    playground = Playground(playground_spec, Map(50, 50, 0.1))

    return playground


@pytest.fixture()
def generate_robot_list():
    r1 = Robot(DiffdriveModel(1.0, 1.0), Footprint([[0, 0]]))
    r2 = Robot(
        DiffdriveModel(1.0, 1.0), Footprint([[0, 0]]), State([1.0, 2.0, 0.0], [])
    )

    return r1, r2


def test_spec(generate_playground):
    playground = generate_playground

    # Testing the specs of the playground.
    assert playground.spec.name == "playground"
    assert playground.spec.dt == 0.01


def test_state_read(generate_playground):
    # Make sure that the correct playground state can be obtained from the
    # playground
    playground = generate_playground
    playground_state = playground.state

    # Making sure that the map is correct.
    assert np.allclose(playground_state.map.data, np.zeros([500, 500]))

    # Making sure that there are currently no robots.
    assert playground_state.num_robots == 0

    # Testing default time.
    assert playground_state.time == 0


def test_state_write(generate_playground, generate_robot_list):
    # Make sure that the returned state is a reference and the value of the
    # actual internal state can be changed through this state.
    playground = generate_playground
    robot1, robot2 = generate_robot_list

    playground_state = playground.state

    # Change time.
    playground_state.time = 0.01

    assert playground.state.time == 0.01

    playground_state.map = Map(np.ones([500, 500]), 0.1)

    # The state value in the Playground object should have changed.
    assert np.allclose(playground.state.map.data, np.ones([500, 500]))

    # Adding a robot through the state. Note that this should never be carried
    # out unless its for testing purposes. Playground's add_robot function
    # must always be used.
    playground_state.add_robot(robot1, 0)
    playground_state.add_robot(robot2, 1)

    # Make sure that the state object and internal playground state both have
    # two robots.
    assert playground_state.num_robots == 2
    assert playground.state.num_robots == 2


def test_get_pilot_oracle(generate_playground, generate_robot_list):
    playground = generate_playground
    robot1, robot2 = generate_robot_list

    pilot1 = CustomPilot([0, 0])
    pilot2 = CustomPilot([1.0, 2])

    # Adding the robots.
    playground.add_robot(robot1, pilot1, IntegratorType.EULER_INTEGRATOR, 1)
    playground.add_robot(robot2, pilot2, IntegratorType.MID_POINT_INTEGRATOR, 2)

    pilot_oracle = playground.get_pilot_oracle()

    # Making sure the oracle is a dict object as is wrapped from an unordered
    # map.
    assert isinstance(pilot_oracle, dict)

    # Length of the dict.
    assert len(pilot_oracle) == 2

    # Individual pilot elements.
    assert np.allclose(pilot_oracle[1].control_input_data, [0, 0])
    assert np.allclose(pilot_oracle[2].control_input_data, [1, 2])

    # Invalid oracle key.
    with pytest.raises(KeyError):
        _ = pilot_oracle[0]
    with pytest.raises(KeyError):
        _ = pilot_oracle[3]


def test_get_pilot(generate_playground, generate_robot_list):
    playground = generate_playground
    robot1, robot2 = generate_robot_list

    pilot1 = CustomPilot([0, 0])
    pilot2 = CustomPilot([1.0, 2])

    # Adding the robots.
    playground.add_robot(robot1, pilot1, IntegratorType.EULER_INTEGRATOR, 1)
    playground.add_robot(robot2, pilot2, IntegratorType.MID_POINT_INTEGRATOR, 2)

    # Making sure the right pilots are returned.
    assert np.allclose(playground.get_pilot(1).control_input_data, [0, 0])
    assert np.allclose(playground.get_pilot(2).control_input_data, [1.0, 2])

    # Invalid uid.
    with pytest.raises(ValueError):
        _ = playground.get_pilot(0)
    with pytest.raises(ValueError):
        _ = playground.get_pilot(3)


def test_get_integrator(generate_playground, generate_robot_list):
    playground = generate_playground
    robot1, robot2 = generate_robot_list

    pilot1 = CustomPilot([0, 0])
    pilot2 = CustomPilot([1.0, 2])

    # Adding the robots.
    playground.add_robot(robot1, pilot1, IntegratorType.MID_POINT_INTEGRATOR, 1)
    playground.add_robot(robot2, pilot2, IntegratorType.RK4_INTEGRATOR, 2)

    # Making sure the right integrators are returned.
    assert isinstance(playground.get_integrator(1), MidPointIntegrator)
    assert isinstance(playground.get_integrator(2), RK4Integrator)

    # Invalid uid.
    with pytest.raises(ValueError):
        _ = playground.get_integrator(0)
    with pytest.raises(ValueError):
        _ = playground.get_integrator(3)


def test_add_robot(generate_playground, generate_robot_list):
    playground = generate_playground
    robot1, robot2 = generate_robot_list

    pilot1 = CustomPilot([0, 0])
    pilot2 = CustomPilot([1.0, 2])

    playground.add_robot(robot1, pilot1, IntegratorType.EULER_INTEGRATOR, 1)
    playground.add_robot(robot2, pilot2, IntegratorType.MID_POINT_INTEGRATOR, 2)

    # Make sure that the robots have been added correctly.
    assert playground.state.num_robots == 2

    assert np.allclose(playground.state.get_robot_state(1).data, robot1.state.data)
    assert np.allclose(playground.state.get_robot_state(2).data, robot2.state.data)


def test_add_robot_with_temporary(generate_playground):
    # Test the function with temporarily created Robot and Pilot objects.
    # This is to test for any cpp lifetime management weirdness.

    playground = generate_playground

    playground.add_robot(
        Robot(DiffdriveModel(1.0, 1.0)),
        CustomPilot([0, 0]),
        IntegratorType.EULER_INTEGRATOR,
        1,
    )
    playground.add_robot(
        Robot(DiffdriveModel(1.0, 1.0)),
        CustomPilot([1, 2]),
        IntegratorType.MID_POINT_INTEGRATOR,
        2,
    )

    # Make sure that the robots have been added correctly.
    assert playground.state.num_robots == 2

    assert np.allclose(playground.state.get_robot_state(1).data, [0.0, 0.0, 0.0])
    assert np.allclose(playground.state.get_robot_state(2).data, [0.0, 0.0, 0.0])


def test_execute(generate_playground, generate_robot_list):
    playground = generate_playground
    robot1, robot2 = generate_robot_list
    pilot1, pilot2 = CustomPilot([0, 0]), CustomPilot([1.0, 1.0])

    # Adding the robots.
    playground.add_robot(robot1, pilot1, IntegratorType.MID_POINT_INTEGRATOR, 1)
    playground.add_robot(robot2, pilot2, IntegratorType.RK4_INTEGRATOR, 2)

    # Make sure that the playground time is 0.
    assert playground.state.time == 0.0

    # Executing a playground cycle.
    playground.execute()

    # Test the states of the robots.
    # The first pilot gives zero control inputs, hence the state must remain
    # unchanged.
    assert np.allclose(playground.state.get_robot_state(1).data, [0.0, 0.0, 0.0])

    # The second robot receives a constant input of [1., 1.]. As the wheel
    # radius = 1 m, the robot moves forward with a velocity of 1 m/s. Hence
    # it moves a total distance of dt m in the x direction (The initial angle
    # is zero).
    assert np.allclose(
        playground.state.get_robot_state(2).data, [1.0 + playground.spec.dt, 2.0, 0.0]
    )

    # Make sure that the playground time has updated.
    assert playground.state.time == playground.spec.dt


def test_execute_with_temporary(generate_playground):
    # Test the function after adding robots using temporarily created Robot and Pilot objects.
    # This is to test for any cpp lifetime management weirdness.

    playground = generate_playground

    playground.add_robot(
        Robot(DiffdriveModel(1.0, 1.0)),
        CustomPilot([0, 0]),
        IntegratorType.EULER_INTEGRATOR,
        1,
    )
    playground.add_robot(
        Robot(DiffdriveModel(1.0, 1.0), initial_state=State([1.0, 2.0, 0.0], [])),
        CustomPilot([1, 1]),
        IntegratorType.MID_POINT_INTEGRATOR,
        2,
    )

    # Make sure that the playground time is 0.
    assert playground.state.time == 0.0

    # Executing a playground cycle.
    playground.execute()

    # Test the states of the robots.
    # The first pilot gives zero control inputs, hence the state must remain
    # unchanged.
    assert np.allclose(playground.state.get_robot_state(1).data, [0.0, 0.0, 0.0])

    # The second robot receives a constant input of [1., 1.]. As the wheel
    # radius = 1 m, the robot moves forward with a velocity of 1 m/s. Hence
    # it moves a total distance of dt m in the x direction (The initial angle
    # is zero).
    assert np.allclose(
        playground.state.get_robot_state(2).data, [1.0 + playground.spec.dt, 2.0, 0.0]
    )

    # Make sure that the playground time has updated.
    assert playground.state.time == playground.spec.dt

