from ._binding_playground_python import (
    PlaygroundSpec,
    PlaygroundState,
    Playground,
)

# Dependencies
# -------------------------------------------------

from morphac.environment._binding_environment_python import (
    Map as _Map,
)

from morphac.math.numeric._binding_numeric_python import (
    Integrator as _Integrator,
)

from morphac.robot.pilot._binding_pilot_python import (
    Pilot as _Pilot,
)


# Adding methods to classes
# -------------------------------------------------

from morphac.simulation.playground import Playground
from morphac.simulation.playground.playground import execute
from morphac.utils.python_utils import add_method_to_class

add_method_to_class(Playground, execute)
