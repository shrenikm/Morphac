from morphac.utils.mechanics_utils import all_model_class_names


def test_all_model_classes():
    model_class_names = all_model_class_names()

    assert model_class_names[0] == "AckermannModel"
    assert model_class_names[1] == "DiffdriveModel"
    assert model_class_names[2] == "DubinModel"
    assert model_class_names[3] == "TricycleModel"
