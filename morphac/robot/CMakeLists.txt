# Directories
# -------------------------------------------------

set(ROBOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(ROBOT_BINARY_DIR ${MORPHAC_BINARY_DIR}/robot)
set(ROBOT_BINDING_BINARY_DIR ${ROBOT_BINARY_DIR}/binding)
set(ROBOT_BINDING_INSTALL_DIR ${PYTHON_BINDING_INSTALL_DIR}/morphac/robot)


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(blueprint)


# Installing
# -------------------------------------------------

# Installing __init__ files.
install(FILES
  ${ROBOT_DIR}/__init__.py
  DESTINATION ${ROBOT_BINDING_INSTALL_DIR}
)

