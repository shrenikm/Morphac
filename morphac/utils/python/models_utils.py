from morphac.mechanics.models import (
    AckermannModel,
    DiffDriveModel,
    DubinModel,
    TricycleModel,
)


# Get a list of the native mechanics models.
def all_model_classes():
    return [
        AckermannModel,
        DiffDriveModel,
        DubinModel,
        TricycleModel,
    ]
