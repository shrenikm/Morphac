from ._binding_blueprint_python import (
    # Footprint interface.
    Footprint,
    # Robot interface.
    Robot,
)

# Importing other module dependencies. This is required because we define the
# python bindings in different namespaces which might not be know to each
# other. For example Robot has the state attribute that returns a State object.
# But this object cannot be parsed correctly through python unless the file
# also imports constructs.State. This is because the bindings for State is
# defined separately under a different namespace which the Robot bindings
# do not know about.

# Dependencies
# -------------------------------------------------

from morphac.constructs._binding_constructs_python import State as _State

from morphac.mechanics.models._binding_models_python import (
    KinematicModel as _KinematicModel,
)
