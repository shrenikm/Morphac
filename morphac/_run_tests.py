import os
import pytest


def get_module_directory():
    return os.path.dirname(__file__)


def run_unit_tests(options, unit_tests_relative_dir):
    unit_tests_abs_path = os.path.join(get_module_directory(), unit_tests_relative_dir)

    assert isinstance(options, list)
    pytest_options = options + [unit_tests_abs_path]
    pytest.main(pytest_options)


def run_all_tests():
    # TODO: Replace with logging.
    print("Running unit tests")
    print("=" * 50)

    # Run unit tests.
    unit_tests_options = []
    unit_tests_relative_dir = "test/unit_tests"
    run_unit_tests(unit_tests_options, unit_tests_relative_dir)


if __name__ == "__main__":
    run_all_tests()
