# Directories
# -------------------------------------------------

set(MECHANICS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(MECHANICS_BINARY_DIR ${MORPHAC_BINARY_DIR}/mechanics)
set(MECHANICS_BINDING_BINARY_DIR ${MECHANICS_BINARY_DIR}/binding)
set(MECHANICS_BINDING_INSTALL_DIR
  ${PYTHON_BINDING_INSTALL_DIR}/morphac/mechanics
)


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(models)
