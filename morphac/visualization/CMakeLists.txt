# Directories
# -------------------------------------------------

set(VISUALIZATION_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(VISUALIZATION_PYTHON_DIR ${VISUALIZATION_DIR}/python)

set(VISUALIZATION_BINARY_DIR ${MORPHAC_BINARY_DIR}/visualization)

# Directories to install the bindings to.
set(VISUALIZATION_PACKAGE_DIR
  ${MORPHAC_PACKAGE_MODULE_DIR}/visualization
)
set(VISUALIZATION_SITE_PACKAGES_DIR
  ${PYTHON_BINDING_INSTALL_DIR}/visualization
)


# Installing
# -------------------------------------------------

# List of python files.
set(VISUALIZATION_PYTHON_FILES
  map_visualization.py
  playground_visualization.py
  robot_visualization.py
)

# Appending the directory of the python files.
prepend_list(VISUALIZATION_PYTHON_FILES
  ${VISUALIZATION_PYTHON_DIR}/
  ${VISUALIZATION_PYTHON_FILES}
)

morphac_package_files(
  ${VISUALIZATION_PACKAGE_DIR}
  ${VISUALIZATION_SITE_PACKAGES_DIR}
  # Files
  ${VISUALIZATION_DIR}/__init__.py
  ${VISUALIZATION_PYTHON_FILES}
)
