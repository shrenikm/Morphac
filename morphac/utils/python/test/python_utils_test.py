import attr
import pytest

from morphac.utils.python_utils import (
    get_class_name,
    add_method_to_class,
    MorphacLogicError,
)


@attr.s(frozen=True, auto_attribs=True)
class CustomClass(object):

    a: float
    b: float


def test_get_class_name():

    obj = CustomClass(2.0, 3.0)

    assert get_class_name(obj) == "CustomClass"


def test_add_method_to_class():
    def _add(self):
        return self.a + self.b

    # There is not add function initially.
    obj = CustomClass(2.0, 3.0)

    with pytest.raises(AttributeError):
        _ = obj.add()

    # Add the function.
    add_method_to_class(CustomClass, _add, "add")

    obj = CustomClass(2.0, 3.0)
    assert obj.add() == 5.0


def test_morphac_logic_error():

    with pytest.raises(MorphacLogicError):
        raise MorphacLogicError("")

