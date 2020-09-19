# Directories
# -------------------------------------------------

set(CONTROLLERS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CONTROLLERS_BINARY_DIR ${MORPHAC_BINARY_DIR}/controllers)
set(CONTROLLERS_BINDING_BINARY_DIR ${CONTROLLERS_BINARY_DIR}/binding)

# Directories to install the bindings to.
set(CONTROLLERS_PACKAGE_DIR
  ${MORPHAC_PACKAGE_MODULE_DIR}/controllers
)
set(CONTROLLERS_SITE_PACKAGES_DIR
  ${MORPHAC_SITE_PACKAGES_DIR}/controllers
)


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(base)
add_subdirectory(basic)


# Installing
# -------------------------------------------------

morphac_package_files(
  ${CONTROLLERS_PACKAGE_DIR}
  ${CONTROLLERS_SITE_PACKAGES_DIR}
  # Files
  ${CONTROLLERS_DIR}/__init__.py
)
