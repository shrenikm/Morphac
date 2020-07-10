from ._binding_playground_python import (
    PlaygroundSpec,
    PlaygroundState,
    Playground,
)

from morphac.simulation.playground import Playground
from morphac.simulation.playground.playground import execute

setattr(Playground, 'execute', execute)
