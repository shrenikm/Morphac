# Directories
# -------------------------------------------------

set(MECHANICS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(MECHANICS_BINARY_DIR ${MORPHAC_BINARY_DIR}/mechanics)
set(MECHANICS_BINDING_BINARY_DIR ${MECHANICS_BINARY_DIR}/binding)

# Directories to install the bindings to.
set(MECHANICS_PACKAGES_INSTALL_DIR
  ${MORPHAC_PACKAGE_MODULE_DIR}/mechanics
)
set(MECHANICS_SITE_PACKAGES_INSTALL_DIR
  ${PYTHON_BINDING_INSTALL_DIR}/mechanics
)


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(models)


# Installing
# -------------------------------------------------

morphac_install_python_package(
  ${MECHANICS_PACKAGES_INSTALL_DIR}
  ${MECHANICS_SITE_PACKAGES_INSTALL_DIR}
  # Files
  ${MECHANICS_DIR}/__init__.py
)

