from ._binding_playground_python import (
    PlaygroundSpec,
    PlaygroundState,
    Playground,
)


from morphac.simulation.playground import Playground
from morphac.simulation.playground.playground import execute
from morphac.utils.python_utils import add_method_to_class

# Adding methods to classes
add_method_to_class(Playground, execute)
