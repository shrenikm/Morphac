def add_method_to_class(cls, method):

    setattr(cls, method.__name__, method)


def get_class_name(obj):

    return obj.__class__.__name__
