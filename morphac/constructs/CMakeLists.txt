# Directories
# -------------------------------------------------

set(CONSTRUCTS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CONSTRUCTS_SRC_DIR ${CONSTRUCTS_DIR}/src)
set(CONSTRUCTS_INCLUDE_DIR ${CONSTRUCTS_DIR}/include)
set(CONSTRUCTS_TEST_DIR ${CONSTRUCTS_DIR}/test)
set(CONSTRUCTS_PYTHON_DIR ${CONSTRUCTS_DIR}/python)

set(CONSTRUCTS_BINARY_DIR ${MORPHAC_BINARY_DIR}/constructs)

set(CONSTRUCTS_BINDING_DIR ${CONSTRUCTS_DIR}/binding)
set(CONSTRUCTS_BINDING_INCLUDE_DIR ${CONSTRUCTS_BINDING_DIR}/include)
set(CONSTRUCTS_BINDING_SRC_DIR ${CONSTRUCTS_BINDING_DIR}/src)
set(CONSTRUCTS_BINDING_BINARY_DIR ${CONSTRUCTS_BINARY_DIR}/binding)

# Directories to install the bindings to.
set(CONSTRUCTS_PACKAGE_DIR
  ${MORPHAC_PACKAGE_MODULE_DIR}/constructs
)
set(CONSTRUCTS_SITE_PACKAGES_DIR
  ${PYTHON_BINDING_INSTALL_DIR}/constructs
)


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(binding)


# Libraries
# -------------------------------------------------

# Constructs source files.
set(CONSTRUCTS_SRC

  coordinate.cc
  control_input.cc
  pose.cc
  state.cc
  trajectory.cc
  velocity.cc
)

morphac_add_libraries(
  ${CONSTRUCTS_INCLUDE_DIR}
  ${CONSTRUCTS_SRC_DIR}
  ${CONSTRUCTS_SRC}
)

# Adding library dependencies.
morphac_link_libraries(state
  pose
  velocity
)

morphac_link_libraries(trajectory
  state
)


# Tests
# -------------------------------------------------

# Constructs tests source files.
set(CONSTRUCTS_TEST_SRC

  coordinate_test.cc
  control_input_test.cc
  pose_test.cc
  state_test.cc
  trajectory_test.cc
  velocity_test.cc
)

# Creating the test executables.
foreach(file ${CONSTRUCTS_TEST_SRC})
  get_filename_component(test_name
    ${file} NAME_WE
  )

  add_executable(
    ${test_name}
    ${CONSTRUCTS_TEST_DIR}/${file}
  )

  add_test(NAME ${test_name}
    COMMAND ${test_name}
  )
endforeach()

# Linking depending libraries.
target_link_libraries(coordinate_test
  PUBLIC
  gtest_main
  coordinate
)

target_link_libraries(control_input_test
  PUBLIC
  gtest_main
  control_input
)

target_link_libraries(pose_test
  PUBLIC
  gtest_main
  pose
)

target_link_libraries(state_test
  PUBLIC
  gtest_main
  state
)

target_link_libraries(trajectory_test
  PUBLIC
  gtest_main
  trajectory
)

target_link_libraries(velocity_test
  PUBLIC
  gtest_main
  velocity
)


# Installing
# -------------------------------------------------

# Install tests.
morphac_package_python_tests(
  ${CONSTRUCTS_PACKAGE_DIR}/test
  ${CONSTRUCTS_SITE_PACKAGES_DIR}/test
  ${CONSTRUCTS_PYTHON_DIR}/test
)
