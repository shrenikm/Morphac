from morphac.mechanics.models import (
    AckermannModel,
    DiffDriveModel,
    DubinModel,
    TricycleModel,
)


def all_standard_model_classes():
    return [
        AckermannModel,
        DiffDriveModel,
        DubinModel,
        TricycleModel,
    ]
