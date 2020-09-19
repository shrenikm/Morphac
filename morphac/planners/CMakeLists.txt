# Directories
# -------------------------------------------------

set(PLANNERS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PLANNERS_BINARY_DIR ${MORPHAC_BINARY_DIR}/planners)
set(PLANNERS_BINDING_BINARY_DIR ${PLANNERS_BINARY_DIR}/binding)

# Directories to install the bindings to.
set(PLANNERS_PACKAGE_DIR
  ${MORPHAC_PACKAGE_MODULE_DIR}/planners
)
set(PLANNERS_SITE_PACKAGES_DIR
  ${PYTHON_BINDING_INSTALL_DIR}/planners
)


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(base)


# Installing
# -------------------------------------------------

morphac_package_files(
  ${PLANNERS_PACKAGE_DIR}
  ${PLANNERS_SITE_PACKAGES_DIR}
  # Files
  ${PLANNERS_DIR}/__init__.py
)

