# Directories
# -------------------------------------------------

set(EXAMPLES_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(EXAMPLES_PYTHON_DIR ${EXAMPLES_DIR}/python)

set(EXAMPLES_BINARY_DIR ${MORPHAC_BINARY_DIR}/examples)

# Directories to install the bindings to.
set(EXAMPLES_PACKAGE_DIR
  ${MORPHAC_PACKAGE_MODULE_DIR}/examples
)
set(EXAMPLES_SITE_PACKAGES_DIR
  ${PYTHON_BINDING_INSTALL_DIR}/examples
)

# Python files
# -------------------------------------------------

# List of python files.
set(EXAMPLES_PYTHON_FILES
  constant_controller_simulation.py
)

# Appending the directory of the python files.
prepend_list(EXAMPLES_PYTHON_FILES
  ${EXAMPLES_PYTHON_DIR}/
  ${EXAMPLES_PYTHON_FILES}
)

morphac_package_files(
  ${EXAMPLES_PACKAGE_DIR}
  ${EXAMPLES_SITE_PACKAGES_DIR}
  # Files
  ${EXAMPLES_DIR}/__init__.py
  ${EXAMPLES_PYTHON_FILES}
)
