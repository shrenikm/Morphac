from functools import wraps


def inject_method(cls):
    def decorator(f):
        @wraps(f)
        def wrapper(self, *args, **kwargs):
            return f(*args, **kwargs)
        # Add the method to the class.
        setattr(cls, func.__name__, wrapper)
        return f
    return decorator
