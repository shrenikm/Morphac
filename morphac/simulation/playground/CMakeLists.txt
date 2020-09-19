# Directories
# -------------------------------------------------

set(PLAYGROUND_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PLAYGROUND_SRC_DIR ${PLAYGROUND_DIR}/src)
set(PLAYGROUND_INCLUDE_DIR ${PLAYGROUND_DIR}/include)
set(PLAYGROUND_TEST_DIR ${PLAYGROUND_DIR}/test)
set(PLAYGROUND_PYTHON_DIR ${PLAYGROUND_DIR}/python)

set(PLAYGROUND_BINARY_DIR ${SIMULATION_BINARY_DIR}/playground)

set(PLAYGROUND_BINDING_DIR ${PLAYGROUND_DIR}/binding)
set(PLAYGROUND_BINDING_INCLUDE_DIR ${PLAYGROUND_BINDING_DIR}/include)
set(PLAYGROUND_BINDING_SRC_DIR ${PLAYGROUND_BINDING_DIR}/src)
set(PLAYGROUND_BINDING_BINARY_DIR ${PLAYGROUND_BINARY_DIR}/binding)

# Directories to install the bindings to.
set(PLAYGROUND_PACKAGE_DIR
  ${SIMULATION_PACKAGE_DIR}/playground
)
set(PLAYGROUND_SITE_PACKAGES_DIR
  ${SIMULATION_SITE_PACKAGES_DIR}/playground
)

# Adding subdirectories
# -------------------------------------------------

add_subdirectory(binding)


# Libraries
# -------------------------------------------------

# Playground source files.
set(PLAYGROUND_SRC

  playground.cc
  playground_spec.cc
  playground_state.cc
)

morphac_add_libraries(
  ${PLAYGROUND_INCLUDE_DIR}
  ${PLAYGROUND_SRC_DIR}
  ${PLAYGROUND_SRC}
)

# Adding library dependencies.
morphac_link_libraries(playground_state
  state
  map
  robot
)

morphac_link_libraries(playground
  playground_spec
  playground_state
  pilot
  integrator
  integrator_utils
)


# Tests
# -------------------------------------------------

# Playground tests source files.
set(PLAYGROUND_TEST_SRC

  playground_spec_test.cc
  playground_state_test.cc
  playground_test.cc
)

# Creating the test executables.
foreach(file ${PLAYGROUND_TEST_SRC})
  get_filename_component(test_name
    ${file} NAME_WE
  )

  add_executable(
    ${test_name}
    ${PLAYGROUND_TEST_DIR}/${file}
  )

  add_test(NAME ${test_name}
    COMMAND ${test_name}
  )
endforeach()

# Linking depending libraries.
target_link_libraries(playground_spec_test
  PUBLIC
  gtest_main
)

target_link_libraries(playground_state_test
  PUBLIC
  gtest_main
  diffdrive_model
  playground_state
)

target_link_libraries(playground_test
  PUBLIC
  gtest_main
  playground
  diffdrive_model
)


# Installing
# -------------------------------------------------

# List of python files.
set(PLAYGROUND_PYTHON_FILES
  playground.py
)

# Appending the directory of the python files.
prepend_list(PLAYGROUND_PYTHON_FILES
  ${PLAYGROUND_PYTHON_DIR}/
  ${PLAYGROUND_PYTHON_FILES}
)

morphac_package_files(
  ${PLAYGROUND_PACKAGE_DIR}
  ${PLAYGROUND_SITE_PACKAGES_DIR}
  # Files
  ${PLAYGROUND_PYTHON_FILES}
)

# Install tests.
morphac_package_python_tests(
  ${MORPHAC_PACKAGE_UNIT_TEST_DIR}
  ${MORPHAC_SITE_PACKAGES_UNIT_TEST_DIR}
  ${PLAYGROUND_PYTHON_DIR}/test
)

