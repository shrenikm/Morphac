# Morphac setup
# -------------------------------------------------

# Including the base morphac directory for relative cpp imports.
set(MORPHAC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${MORPHAC_DIR})

# Base morphac binary directory.
set(MORPHAC_BINARY_DIR ${CMAKE_BINARY_DIR}/${MORPHAC_NAME})

# Run tests script file.
set(MORPHAC_PYTHON_RUN_TESTS_SCRIPT_FILE ${MORPHAC_DIR}/_run_tests.py)
# File name to be renamed to during installation.
set(MORPHAC_PYTHON_RUN_TESTS_SCRIPT_FILENAME run_tests.py)


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
morphac_package_files(
  ${MORPHAC_PACKAGE_MODULE_DIR}
  ${MORPHAC_SITE_PACKAGES_DIR}
  # Files
  ${MORPHAC_DIR}/__init__.py
)

# Install the run_tests script.
morphac_package_file(
  ${MORPHAC_PACKAGE_MODULE_DIR}
  ${MORPHAC_SITE_PACKAGES_DIR}
  ${MORPHAC_PYTHON_RUN_TESTS_SCRIPT_FILE}
  ${MORPHAC_PYTHON_RUN_TESTS_SCRIPT_FILENAME}

)


