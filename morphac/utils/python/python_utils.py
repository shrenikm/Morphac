def add_method_to_class(cls, method):

    setattr(cls, method.__name__, method)


def get_class_name(obj):

    return obj.__class__.__name__


# Custom exceptions.
# -------------------------------------------------


class MorphacLogicError(Exception):
    def __init__(self, message):
        self.message = message

    def __str__(self):
        # TODO: Convert to f strings if Python 3.5 support is dropped.
        return "Logic error: {}".format(self.message)
