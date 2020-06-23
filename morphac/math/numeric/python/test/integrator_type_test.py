import pytest

from morphac.math.numeric import IntegratorType


@pytest.fixture()
def generator_integrator_type():

    euler_type = IntegratorType.EULER_INTEGRATOR
    mid_point_type = IntegratorType.MID_POINT_INTEGRATOR
    rk4_type = IntegratorType.RK4_INTEGRATOR

    return euler_type, mid_point_type, rk4_type


def test_type_equality(generator_integrator_type):
    euler_type, mid_point_type, rk4_type = generator_integrator_type

    assert euler_type == IntegratorType.EULER_INTEGRATOR
    assert mid_point_type == IntegratorType.MID_POINT_INTEGRATOR
    assert rk4_type == IntegratorType.RK4_INTEGRATOR

    assert euler_type is IntegratorType.EULER_INTEGRATOR
    assert mid_point_type is IntegratorType.MID_POINT_INTEGRATOR
    assert rk4_type is IntegratorType.RK4_INTEGRATOR

    assert euler_type != IntegratorType.MID_POINT_INTEGRATOR
    assert mid_point_type != IntegratorType.RK4_INTEGRATOR
    assert rk4_type != IntegratorType.EULER_INTEGRATOR

    assert euler_type is not IntegratorType.MID_POINT_INTEGRATOR
    assert mid_point_type is not IntegratorType.RK4_INTEGRATOR
    assert rk4_type is not IntegratorType.EULER_INTEGRATOR
