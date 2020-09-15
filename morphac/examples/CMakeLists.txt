# Directories
# -------------------------------------------------

set(EXAMPLES_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(EXAMPLES_PYTHON_DIR ${EXAMPLES_DIR}/python)

set(EXAMPLES_BINARY_DIR ${MORPHAC_BINARY_DIR}/examples)

set(EXAMPLES_BINDING_INSTALL_DIR
  ${PYTHON_BINDING_INSTALL_DIR}/examples
)

# Python files
# -------------------------------------------------

# Installing __init__ files.
install(FILES
  ${EXAMPLES_DIR}/__init__.py
  DESTINATION
  ${EXAMPLES_BINDING_INSTALL_DIR}
)

# List of python files.
set(EXAMPLES_PYTHON_FILES
  constant_controller_simulation.py
)

# Appending the directory of the python files.
prepend_list(EXAMPLES_PYTHON_FILES
  ${EXAMPLES_PYTHON_DIR}/
  ${EXAMPLES_PYTHON_FILES}
)

# Install the python files.
install(FILES
  ${EXAMPLES_PYTHON_FILES}
  DESTINATION
  ${EXAMPLES_BINDING_INSTALL_DIR}
)
