from morphac.mechanics.models import (
    AckermannModel,
    DiffdriveModel,
    DubinModel,
    TricycleModel,
)


# Get a list of the native mechanics models.
def all_model_classes():

    return [
        "AckermannModel",
        "DiffdriveModel",
        "DubinModel",
        "TricycleModel",
    ]
