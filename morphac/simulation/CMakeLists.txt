# Directories
# -------------------------------------------------

set(SIMULATION_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SIMULATION_BINARY_DIR ${MORPHAC_BINARY_DIR}/simulation)
set(SIMULATION_BINDING_BINARY_DIR ${SIMULATION_BINARY_DIR}/binding)
set(SIMULATION_BINDING_INSTALL_DIR ${PYTHON_BINDING_INSTALL_DIR}/simulation)


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(playground)


# Installing
# -------------------------------------------------

# Installing __init__ files.
install(FILES
  ${SIMULATION_DIR}/__init__.py
  DESTINATION
  ${SIMULATION_BINDING_INSTALL_DIR}
)

