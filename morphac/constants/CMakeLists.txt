# Directories
# -------------------------------------------------

set(CONSTANTS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CONSTANTS_PYTHON_DIR ${CONSTANTS_DIR}/python)

set(CONSTANTS_BINARY_DIR ${MORPHAC_BINARY_DIR}/constants)

set(CONSTANTS_BINDING_INSTALL_DIR
  ${PYTHON_BINDING_INSTALL_DIR}/constants
)

# Python files
# -------------------------------------------------

# Installing __init__ files.
install(FILES
  ${CONSTANTS_DIR}/__init__.py
  DESTINATION
  ${CONSTANTS_BINDING_INSTALL_DIR}
)

# List of python files.
set(CONSTANTS_PYTHON_FILES
  colors.py
)

# Appending the directory of the python files.
prepend_list(CONSTANTS_PYTHON_FILES
  ${CONSTANTS_PYTHON_DIR}/
  ${CONSTANTS_PYTHON_FILES}
)

# Install the python files.
install(FILES
  ${CONSTANTS_PYTHON_FILES}
  DESTINATION
  ${CONSTANTS_BINDING_INSTALL_DIR}
)
