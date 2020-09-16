# Morphac setup
# -------------------------------------------------

# Including the base morphac directory for relative cpp imports.
set(MORPHAC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${MORPHAC_DIR})

# Base morphac binary directory.
set(MORPHAC_BINARY_DIR ${CMAKE_BINARY_DIR}/${MORPHAC_NAME})

# Python package directory. Note that this is different from the python bindings
# install directory. This directory includes all of the compiled objects that make
# up the pip installation package.
set(MORPHAC_PYTHON_PACKAGE_DIR ${CMAKE_SOURCE_DIR}/package/${MORPHAC_NAME})

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

# Installing __init__ files.
install(FILES
  ${MORPHAC_DIR}/__init__.py
  DESTINATION
  ${PYTHON_BINDING_INSTALL_DIR}
)

# Install into the package.
if(CREATE_PYTHON_PACKAGE)
  install(FILES
    ${MORPHAC_DIR}/__init__.py
    DESTINATION
    ${MORPHAC_PYTHON_PACKAGE_DIR}
  )
endif()
