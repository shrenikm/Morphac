import pytest

from morphac.constants import (
    AckermannModelConstants,
    DiffdriveModelConstants,
    DubinModelConstants,
    TricycleModelConstants,
)


def test_ackermann_model_constants():

    assert AckermannModelConstants.DEFAULT_WHEEL_DIAMETER_SCALER == 0.25
    assert AckermannModelConstants.DEFAULT_WHEEL_SIZE_RATIO == 3.0
    assert AckermannModelConstants.DEFAULT_WIDTH_BUFFER_SCALER == 0.25 / 3.0
    assert AckermannModelConstants.DEFAULT_WIDTH_BUFFER == 0.2
    assert AckermannModelConstants.DEFAULT_LENGTH_BUFFER_SCALER == 0.25
    assert AckermannModelConstants.DEFAULT_LENGTH_BUFFER == 0.2


def test_set_ackermann_model_constants():

    # The values should not be modifiable.
    with pytest.raises(AttributeError):
        AckermannModelConstants.DEFAULT_WHEEL_DIAMETER_SCALER = 0.0
    with pytest.raises(AttributeError):
        AckermannModelConstants.DEFAULT_WHEEL_SIZE_RATIO = 0.0
    with pytest.raises(AttributeError):
        AckermannModelConstants.DEFAULT_WIDTH_BUFFER_SCALER = 0.0
    with pytest.raises(AttributeError):
        AckermannModelConstants.DEFAULT_WIDTH_BUFFER = 0.0
    with pytest.raises(AttributeError):
        AckermannModelConstants.DEFAULT_LENGTH_BUFFER_SCALER = 0.0
    with pytest.raises(AttributeError):
        AckermannModelConstants.DEFAULT_LENGTH_BUFFER = 0.0


def test_diffdrive_model_constants():

    assert DiffdriveModelConstants.DEFAULT_WHEEL_SIZE_RATIO == 3.0
    assert DiffdriveModelConstants.DEFAULT_RADIUS_BUFFER_SCALER == 0.25
    assert DiffdriveModelConstants.DEFAULT_RADIUS_BUFFER == 0.0


def test_set_diffdrive_model_constants():

    # The values should not be modifiable.
    with pytest.raises(AttributeError):
        DiffdriveModelConstants.DEFAULT_WHEEL_SIZE_RATIO = 0.0
    with pytest.raises(AttributeError):
        DiffdriveModelConstants.DEFAULT_RADIUS_BUFFER_SCALER = 0.0
    with pytest.raises(AttributeError):
        DiffdriveModelConstants.DEFAULT_RADIUS_BUFFER = 0.0


def test_dubin_model_constants():

    assert DubinModelConstants.DEFAULT_BASE == 0.5
    assert DubinModelConstants.DEFAULT_HEIGHT == 0.5


def test_set_dubin_model_constants():

    # The values should not be modifiable.

    with pytest.raises(AttributeError):
        DubinModelConstants.DEFAULT_BASE = 0.0
    with pytest.raises(AttributeError):
        DubinModelConstants.DEFAULT_HEIGHT = 0.0


def test_tricycle_model_constants():

    assert TricycleModelConstants.DEFAULT_FRONT_WHEEL_DIAMETER_SCALER == 0.3
    assert TricycleModelConstants.DEFAULT_FRONT_WHEEL_SIZE_RATIO == 3.0
    assert TricycleModelConstants.DEFAULT_BACK_WHEEL_DIAMETER_SCALER == 0.2
    assert TricycleModelConstants.DEFAULT_BACK_WHEEL_SIZE_RATIO == 3.0
    assert TricycleModelConstants.DEFAULT_WIDTH_BUFFER_SCALER == 0.2 / 3.0
    assert TricycleModelConstants.DEFAULT_WIDTH_BUFFER == 0.2
    assert TricycleModelConstants.DEFAULT_LENGTH_BUFFER_SCALER == 0.25
    assert TricycleModelConstants.DEFAULT_LENGTH_BUFFER == 0.2


def test_set_tricycle_model_constants():

    # The values should not be modifiable.
    with pytest.raises(AttributeError):
        TricycleModelConstants.DEFAULT_FRONT_WHEEL_DIAMETER_SCALER = 0.0
    with pytest.raises(AttributeError):
        TricycleModelConstants.DEFAULT_FRONT_WHEEL_SIZE_RATIO = 0.0
    with pytest.raises(AttributeError):
        TricycleModelConstants.DEFAULT_BACK_WHEEL_DIAMETER_SCALER = 0.0
    with pytest.raises(AttributeError):
        TricycleModelConstants.DEFAULT_BACK_WHEEL_SIZE_RATIO = 0.0
    with pytest.raises(AttributeError):
        TricycleModelConstants.DEFAULT_WIDTH_BUFFER_SCALER = 0.0
    with pytest.raises(AttributeError):
        TricycleModelConstants.DEFAULT_WIDTH_BUFFER = 0.0
    with pytest.raises(AttributeError):
        TricycleModelConstants.DEFAULT_LENGTH_BUFFER_SCALER = 0.0
    with pytest.raises(AttributeError):
        TricycleModelConstants.DEFAULT_LENGTH_BUFFER = 0.0
