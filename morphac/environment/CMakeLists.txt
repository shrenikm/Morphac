# Directories
# -------------------------------------------------

set(ENVIRONMENT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(ENVIRONMENT_SRC_DIR ${ENVIRONMENT_DIR}/src)
set(ENVIRONMENT_INCLUDE_DIR ${ENVIRONMENT_DIR}/include)
set(ENVIRONMENT_TEST_DIR ${ENVIRONMENT_DIR}/test)
set(ENVIRONMENT_PYTHON_DIR ${ENVIRONMENT_DIR}/python)

set(ENVIRONMENT_BINARY_DIR ${MORPHAC_BINARY_DIR}/environment)

set(ENVIRONMENT_BINDING_DIR ${ENVIRONMENT_DIR}/binding)
set(ENVIRONMENT_BINDING_INCLUDE_DIR ${ENVIRONMENT_BINDING_DIR}/include)
set(ENVIRONMENT_BINDING_SRC_DIR ${ENVIRONMENT_BINDING_DIR}/src)
set(ENVIRONMENT_BINDING_BINARY_DIR ${ENVIRONMENT_BINARY_DIR}/binding)

# Directories to install the bindings to.
set(ENVIRONMENT_PACKAGE_DIR
  ${MORPHAC_PACKAGE_MODULE_DIR}/environment
)
set(ENVIRONMENT_SITE_PACKAGES_DIR
  ${MORPHAC_SITE_PACKAGES_DIR}/environment
)


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(binding)


# Libraries
# -------------------------------------------------

# Environment source files.
set(ENVIRONMENT_SRC

  map.cc
)

morphac_add_libraries(
  ${ENVIRONMENT_INCLUDE_DIR}
  ${ENVIRONMENT_SRC_DIR}
  ${ENVIRONMENT_SRC}
)


# Tests
# -------------------------------------------------

# Environment tests source files.
set(ENVIRONMENT_TEST_SRC

  map_test.cc
)

# Creating the test executables.
foreach(file ${ENVIRONMENT_TEST_SRC})
  get_filename_component(test_name
    ${file} NAME_WE
  )

  add_executable(
    ${test_name}
    ${ENVIRONMENT_TEST_DIR}/${file}
  )

  add_test(NAME ${test_name}
    COMMAND ${test_name}
  )
endforeach()

# Linking depending libraries.
target_link_libraries(map_test
  PUBLIC
  gtest_main
  map
)


# Installing
# -------------------------------------------------

# List of python files.
set(ENVIRONMENT_PYTHON_FILES
  _map.py
)

# Appending the directory of the python files.
prepend_list(ENVIRONMENT_PYTHON_FILES
  ${ENVIRONMENT_PYTHON_DIR}/
  ${ENVIRONMENT_PYTHON_FILES}
)

morphac_package_files(
  ${ENVIRONMENT_PACKAGE_DIR}
  ${ENVIRONMENT_SITE_PACKAGES_DIR}
  # Files
  ${ENVIRONMENT_PYTHON_FILES}
)

# Install tests.
morphac_package_python_tests(
  ${MORPHAC_PACKAGE_UNIT_TEST_DIR}
  ${MORPHAC_SITE_PACKAGES_UNIT_TEST_DIR}
  ${ENVIRONMENT_PYTHON_DIR}/test
)

