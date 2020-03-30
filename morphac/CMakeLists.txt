# Morphac setup
# -------------------------------------------------

# Including the base morphac directory for relative cpp imports.
set(MORPHAC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${MORPHAC_DIR})

# Base morphac binary directory.
set(MORPHAC_BINARY_DIR ${CMAKE_BINARY_DIR}/morphac)

# Adding subdirectories
# -------------------------------------------------

add_subdirectory(constructs)
add_subdirectory(environments)
add_subdirectory(mechanics)
add_subdirectory(robot)


# Installing
# -------------------------------------------------

# Installing __init__ files.
install(FILES
  ${MORPHAC_DIR}/__init__.py
  DESTINATION ${PYTHON_BINDING_INSTALL_DIR}/morphac
)
