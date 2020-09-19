# Directories
# -------------------------------------------------

set(ROBOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(ROBOT_BINARY_DIR ${MORPHAC_BINARY_DIR}/robot)
set(ROBOT_BINDING_BINARY_DIR ${ROBOT_BINARY_DIR}/binding)

# Directories to install the bindings to.
set(ROBOT_PACKAGE_DIR
  ${MORPHAC_PACKAGE_MODULE_DIR}/robot
)
set(ROBOT_SITE_PACKAGES_DIR
  ${PYTHON_BINDING_INSTALL_DIR}/robot
)


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(blueprint)
add_subdirectory(pilot)


# Installing
# -------------------------------------------------

morphac_package_files(
  ${ROBOT_PACKAGE_DIR}
  ${ROBOT_SITE_PACKAGES_DIR}
  # Files
  ${ROBOT_DIR}/__init__.py
)

