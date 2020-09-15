import numpy as np
import pytest

from morphac.constructs import State, ControlInput
from morphac.math.numeric import (
    IntegratorType,
    EulerIntegrator,
    MidPointIntegrator,
    RK4Integrator,
)
from morphac.mechanics.models import DiffdriveModel
from morphac.utils.integrator_utils import integrator_from_type


@pytest.fixture
def generate_integrator_list():

    integrator_type_list = [
        IntegratorType.EULER_INTEGRATOR,
        IntegratorType.MID_POINT_INTEGRATOR,
        IntegratorType.RK4_INTEGRATOR,
    ]
    integrator_class_list = [EulerIntegrator, MidPointIntegrator, RK4Integrator]

    return integrator_type_list, integrator_class_list


def test_construction(generate_integrator_list):

    integrator_type_list, integrator_class_list = generate_integrator_list
    kinematic_model = DiffdriveModel(1.0, 1.0)

    # Making sure that the right integrator is constructed.
    for integrator_type, integrator_class in zip(
        integrator_type_list, integrator_class_list
    ):
        integrator = integrator_from_type(
            integrator_type=integrator_type, kinematic_model=kinematic_model
        )
        assert isinstance(integrator, integrator_class)

        # Also making sure that the integrator is usable.
        assert np.allclose(
            integrator.step(State(3, 0), ControlInput(2), 0.05).data, [0.0, 0.0, 0.0]
        )


def test_construction_with_temporary(generate_integrator_list):
    # Test the function with a temporarily created KinematicModel object.
    # This is to test for any cpp lifetime management weirdness.
    integrator_type_list, integrator_class_list = generate_integrator_list

    # Making sure that the right integrator is constructed.
    for integrator_type, integrator_class in zip(
        integrator_type_list, integrator_class_list
    ):
        integrator = integrator_from_type(integrator_type, DiffdriveModel(1.0, 1.0))

        assert isinstance(integrator, integrator_class)

        # Also making sure that the integrator is usable.
        assert np.allclose(
            integrator.step(State(3, 0), ControlInput(2), 0.05).data, [0.0, 0.0, 0.0]
        )
