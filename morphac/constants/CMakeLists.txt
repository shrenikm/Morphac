# Directories
# -------------------------------------------------

set(CONSTANTS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CONSTANTS_SRC_DIR ${CONSTANTS_DIR}/src)
set(CONSTANTS_INCLUDE_DIR ${CONSTANTS_DIR}/include)
set(CONSTANTS_TEST_DIR ${CONSTANTS_DIR}/test)
set(CONSTANTS_PYTHON_DIR ${CONSTANTS_DIR}/python)

set(CONSTANTS_BINARY_DIR ${MORPHAC_BINARY_DIR}/constants)

set(CONSTANTS_BINDING_DIR ${CONSTANTS_DIR}/binding)
set(CONSTANTS_BINDING_INCLUDE_DIR ${CONSTANTS_BINDING_DIR}/include)
set(CONSTANTS_BINDING_SRC_DIR ${CONSTANTS_BINDING_DIR}/src)
set(CONSTANTS_BINDING_MODULES_DIR
  ${CONSTANTS_BINDING_DIR}/modules
)
set(CONSTANTS_BINDING_BINARY_DIR ${CONSTANTS_BINARY_DIR}/binding)

# Directories to install the bindings to.
set(CONSTANTS_PACKAGES_INSTALL_DIR
  ${MORPHAC_PYTHON_PACKAGE_DIR}/constants
)
set(CONSTANTS_SITE_PACKAGES_INSTALL_DIR
  ${PYTHON_BINDING_INSTALL_DIR}/constants
)


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(binding)


# Libraries
# -------------------------------------------------

# Constants source files.
set(CONSTANTS_SRC

  environment_constants.cc
  mechanics_constants.cc
)

morphac_add_libraries(
  ${CONSTANTS_INCLUDE_DIR}
  ${CONSTANTS_SRC_DIR}
  ${CONSTANTS_SRC}
)


# Tests
# -------------------------------------------------

# Constants tests source files.
set(CONSTANTS_TEST_SRC

  environment_constants_test.cc
  mechanics_constants_test.cc
)

# Creating the test executables.
foreach(file ${CONSTANTS_TEST_SRC})
  get_filename_component(test_name
    ${file} NAME_WE
  )

  add_executable(
    ${test_name}
    ${CONSTANTS_TEST_DIR}/${file}
  )

  add_test(NAME ${test_name}
    COMMAND ${test_name}
  )
endforeach()

# Linking depending libraries.
target_link_libraries(environment_constants_test
  PUBLIC
  gtest_main
  environment_constants
)

target_link_libraries(mechanics_constants_test
  PUBLIC
  gtest_main
  mechanics_constants
)


# Installing
# -------------------------------------------------

# List of python files to install.
set(CONSTANTS_PYTHON_FILES
  colors.py
)

# Appending the directory of the python files.
prepend_list(CONSTANTS_PYTHON_FILES
  ${CONSTANTS_PYTHON_DIR}/
  ${CONSTANTS_PYTHON_FILES}
)

morphac_install_python_package(
  ${CONSTANTS_PACKAGES_INSTALL_DIR}
  ${CONSTANTS_SITE_PACKAGES_INSTALL_DIR}
  # Files
  ${CONSTANTS_PYTHON_FILES}
)

