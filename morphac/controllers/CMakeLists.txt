# Directories
# -------------------------------------------------

set(CONTROLLERS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CONTROLLERS_BINARY_DIR ${MORPHAC_BINARY_DIR}/controllers)
set(CONTROLLERS_BINDING_BINARY_DIR ${CONTROLLERS_BINARY_DIR}/binding)
set(CONTROLLERS_BINDING_INSTALL_DIR ${PYTHON_BINDING_INSTALL_DIR}/controllers)


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(base)
add_subdirectory(basic)


# Installing
# -------------------------------------------------

# Installing __init__ files.
install(FILES
  ${CONTROLLERS_DIR}/__init__.py
  DESTINATION
  ${CONTROLLERS_BINDING_INSTALL_DIR}
)
