def get_class_name(obj):

    return obj.__class__.__name__


def add_method_to_class(cls, method, method_name=None):
    # If no method name is provided explicitly, keep the same name.
    if method_name is None:
        method_name = method.__name__

    setattr(cls, method_name, method)


# Custom exceptions.
# -------------------------------------------------


class MorphacLogicError(Exception):
    def __init__(self, message):
        self.message = message

    def __str__(self):
        return f"Logic error: {self.message}"


class MorphacVisualizationError(MorphacLogicError):
    def __init__(self, message):
        super().__init__(message)

    def __str__(self):
        return f"Logic error: {self.message}"
