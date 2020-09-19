# Morphac setup
# -------------------------------------------------

# Including the base morphac directory for relative cpp imports.
set(MORPHAC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${MORPHAC_DIR})

# Base morphac binary directory.
set(MORPHAC_BINARY_DIR ${CMAKE_BINARY_DIR}/${MORPHAC_NAME})

# Set up version and setup files.
# The version and setup files in the main directory are named _version.py and _setup.py
# During installation to the packages, they are installed after stripping the underscore.
set(MORPHAC_PYTHON_VERSION_FILE ${CMAKE_SOURCE_DIR}/_version.py)
set(MORPHAC_PYTHON_PACKAGE_VERSION_FILENAME version.py)
# Write the version into version.py
FILE(WRITE ${MORPHAC_PYTHON_VERSION_FILE} "__version__ = '${PROJECT_VERSION}'")

set(MORPHAC_PYTHON_SETUP_FILE ${CMAKE_SOURCE_DIR}/_setup.py)
set(MORPHAC_PYTHON_PACKAGE_SETUP_FILENAME setup.py)


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

# Installing the version and setup files.
morphac_install_python_file(
  ${MORPHAC_PYTHON_PACKAGE_DIR}
  ${PYTHON_BINDING_INSTALL_DIR}
  ${MORPHAC_PYTHON_VERSION_FILE}
  ${MORPHAC_PYTHON_PACKAGE_VERSION_FILENAME}
)

morphac_install_python_file(
  ${MORPHAC_PYTHON_PACKAGE_DIR}
  ${PYTHON_BINDING_INSTALL_DIR}
  ${MORPHAC_PYTHON_SETUP_FILE}
  ${MORPHAC_PYTHON_PACKAGE_SETUP_FILENAME}
)

# Installing the main __init__ file.
morphac_install_python_package(
  ${MORPHAC_PYTHON_PACKAGE_DIR}
  ${PYTHON_BINDING_INSTALL_DIR}
  # Files
  ${MORPHAC_DIR}/__init__.py
)


