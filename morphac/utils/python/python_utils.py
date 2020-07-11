def add_method_to_class(cls, method):
    setattr(cls, method.__name__, method)
