from morphac.utils.mechanics_utils import all_model_classes


def test_all_model_classes():
    model_classes = all_model_classes()

    assert model_classes[0] == "AckermannModel"
    assert model_classes[1] == "DiffdriveModel"
    assert model_classes[2] == "DubinModel"
    assert model_classes[3] == "TricycleModel"
