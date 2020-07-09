import pytest

from morphac.simulation.playground import PlaygroundSpec


@pytest.fixture()
def generate_playground_spec_list():
    ps1 = PlaygroundSpec("playground1", 0.001, 10, 10)
    ps2 = PlaygroundSpec(name="playground2", dt=0.02,
                         gui_width=1000, gui_height=900)

    return ps1, ps2


def test_attributes(generate_playground_spec_list):
    ps1, ps2 = generate_playground_spec_list

    # Test the attributes of the Spec objects.
    assert ps1.name == "playground1"
    assert ps1.dt == 0.001
    assert ps1.gui_width == 10
    assert ps1.gui_height == 10

    assert ps2.name == "playground2"
    assert ps2.dt == 0.02
    assert ps2.gui_width == 1000
    assert ps2.gui_height == 900
