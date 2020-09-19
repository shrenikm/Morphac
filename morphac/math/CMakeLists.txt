# Directories
# -------------------------------------------------

set(MATH_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(MATH_BINARY_DIR ${MORPHAC_BINARY_DIR}/math)
set(MATH_BINDING_BINARY_DIR ${MATH_BINARY_DIR}/binding)

# Directories to install the bindings to.
set(MATH_PACKAGE_DIR
  ${MORPHAC_PACKAGE_MODULE_DIR}/math
)
set(MATH_SITE_PACKAGES_DIR
  ${PYTHON_BINDING_INSTALL_DIR}/math
)


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(numeric)
add_subdirectory(geometry)
add_subdirectory(transforms)


# Installing
# -------------------------------------------------

morphac_package_files(
  ${MATH_PACKAGE_DIR}
  ${MATH_SITE_PACKAGES_DIR}
  # Files
  ${MATH_DIR}/__init__.py
)

