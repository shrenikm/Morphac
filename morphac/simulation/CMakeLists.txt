# Directories
# -------------------------------------------------

set(SIMULATION_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SIMULATION_BINARY_DIR ${MORPHAC_BINARY_DIR}/simulation)
set(SIMULATION_BINDING_BINARY_DIR ${SIMULATION_BINARY_DIR}/binding)

# Directories to install the bindings to.
set(SIMULATION_PACKAGES_INSTALL_DIR
  ${MORPHAC_PACKAGE_MODULE_DIR}/simulation
)
set(SIMULATION_SITE_PACKAGES_INSTALL_DIR
  ${PYTHON_BINDING_INSTALL_DIR}/simulation
)

# Adding subdirectories
# -------------------------------------------------

add_subdirectory(playground)


# Installing
# -------------------------------------------------

morphac_install_python_package(
  ${SIMULATION_PACKAGES_INSTALL_DIR}
  ${SIMULATION_SITE_PACKAGES_INSTALL_DIR}
  # Files
  ${SIMULATION_DIR}/__init__.py
)


