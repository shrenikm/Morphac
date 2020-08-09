import attrs

from morphac.mechanics.models import KinematicModel
from morphac.utils.mechanics_utils import all_standard_model_classes


def _ackermann_drawing_kernel(canvas, robot):
    pass


def _diffdrive_drawing_kernel(canvas, robot):
    pass


def _dubin_drawing_kernel(canvas, robot):
    pass


def _tricycle_drawing_kernel(canvas, robot):
    pass


def _get_standard_model_kernel_correspondence():
    model_classes = all_standard_model_classes()
    return {
        model_classes[0]: _ackermann_drawing_kernel,
        model_classes[1]: _diffdrive_drawing_kernel,
        model_classes[2]: _dubin_drawing_kernel,
        model_classes[3]: _tricycle_drawing_kernel,
    }


@attr.s
RobotVisualizer(object):

    _model_kernel_correspondence = attr.ib(
        type=dict,
        init=False,
        default=_get_standard_model_kernel_correspondence()
    )

    def add_correspondence(model_class, drawing_kernel):
        assert isinstance(model_class, KinematicModel)
        self._model_kernel_correspondence[model_class] = drawing_kernel
