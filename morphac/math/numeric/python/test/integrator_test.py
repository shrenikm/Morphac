import numpy as np
import pytest

from morphac.math.numeric import Integrator
from morphac.mechanics.models import DiffDriveModel

# Class that extends from Integrator. Testing if a functional subclass of the
# pybind binding of Integrator can be built.
