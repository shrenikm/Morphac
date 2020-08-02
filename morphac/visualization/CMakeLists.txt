# Directories
# -------------------------------------------------

set(VISUALIZATION_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(VISUALIZATION_PYTHON_DIR ${VISUALIZATION_DIR}/python)

set(VISUALIZATION_BINARY_DIR ${MORPHAC_BINARY_DIR}/visualization)

set(VISUALIZATION_BINDING_INSTALL_DIR
  ${PYTHON_BINDING_INSTALL_DIR}/visualization
)

# Python files
# -------------------------------------------------

# Installing __init__ files.
install(FILES
  ${VISUALIZATION_DIR}/__init__.py
  DESTINATION
  ${VISUALIZATION_BINDING_INSTALL_DIR}
)

# List of python files.
set(VISUALIZATION_PYTHON_FILES
  map_visualization.py
  playground_visualization.py
)

# Appending the directory of the python files.
prepend_list(VISUALIZATION_PYTHON_FILES
  ${VISUALIZATION_PYTHON_DIR}/
  ${VISUALIZATION_PYTHON_FILES}
)

# Install the python files.
install(FILES
  ${VISUALIZATION_PYTHON_FILES}
  DESTINATION
  ${VISUALIZATION_BINDING_INSTALL_DIR}
)
