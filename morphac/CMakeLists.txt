# Morphac setup
# -------------------------------------------------

# Including the base morphac directory for relative cpp imports.
set(MORPHAC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${MORPHAC_DIR})

# Base morphac binary directory.
set(MORPHAC_BINARY_DIR ${CMAKE_BINARY_DIR}/${MORPHAC_NAME})


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(constants)
add_subdirectory(constructs)
add_subdirectory(controllers)
add_subdirectory(environment)
add_subdirectory(examples)
add_subdirectory(math)
add_subdirectory(mechanics)
add_subdirectory(planners)
add_subdirectory(robot)
add_subdirectory(simulation)
add_subdirectory(utils)
add_subdirectory(visualization)


# Installing
# -------------------------------------------------

# Installing the main __init__ file.
morphac_install_python_package(
  ${MORPHAC_PACKAGE_MODULE_DIR}
  ${PYTHON_BINDING_INSTALL_DIR}
  # Files
  ${MORPHAC_DIR}/__init__.py
)


