# Directories
# -------------------------------------------------

set(BLUEPRINT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BLUEPRINT_SRC_DIR ${BLUEPRINT_DIR}/src)
set(BLUEPRINT_INCLUDE_DIR ${BLUEPRINT_DIR}/include)
set(BLUEPRINT_TEST_DIR ${BLUEPRINT_DIR}/test)
set(BLUEPRINT_PYTHON_DIR ${BLUEPRINT_DIR}/python)

set(BLUEPRINT_BINARY_DIR ${ROBOT_BINARY_DIR}/blueprint)

set(BLUEPRINT_BINDING_DIR ${BLUEPRINT_DIR}/binding)
set(BLUEPRINT_BINDING_INCLUDE_DIR ${BLUEPRINT_BINDING_DIR}/include)
set(BLUEPRINT_BINDING_SRC_DIR ${BLUEPRINT_BINDING_DIR}/src)
set(BLUEPRINT_BINDING_BINARY_DIR ${BLUEPRINT_BINARY_DIR}/binding)

# Directories to install the bindings to.
set(BLUEPRINT_PACKAGE_DIR
  ${ROBOT_PACKAGE_DIR}/blueprint
)
set(BLUEPRINT_SITE_PACKAGES_DIR
  ${ROBOT_SITE_PACKAGES_DIR}/blueprint
)


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(binding)


# Libraries
# -------------------------------------------------

# Blueprint source files.
set(BLUEPRINT_SRC

  footprint.cc
  robot.cc
)

morphac_add_libraries(
  ${BLUEPRINT_INCLUDE_DIR}
  ${BLUEPRINT_SRC_DIR}
  ${BLUEPRINT_SRC}
)

# Adding library dependencies.
morphac_link_libraries(footprint
  TRUE
  coordinate
  polygons
)

morphac_link_libraries(robot
  TRUE
  control_input
  state
  kinematic_model
  footprint
)


# Tests
# -------------------------------------------------

# Blueprint tests source files.
set(BLUEPRINT_TEST_SRC

  footprint_test.cc
  robot_test.cc
)

# Creating the test executables.
foreach(file ${BLUEPRINT_TEST_SRC})
  get_filename_component(test_name
    ${file} NAME_WE
  )

  add_executable(
    ${test_name}
    ${BLUEPRINT_TEST_DIR}/${file}
  )

  add_test(NAME ${test_name}
    COMMAND ${test_name}
  )
endforeach()

# Linking depending libraries.
target_link_libraries(footprint_test
  PUBLIC
  gtest_main
  footprint
)

target_link_libraries(robot_test
  PUBLIC
  gtest_main
  robot
)


# Installing
# -------------------------------------------------

# Install tests.
morphac_package_python_tests(
  ${MORPHAC_PACKAGE_UNIT_TEST_DIR}
  ${MORPHAC_SITE_PACKAGES_UNIT_TEST_DIR}
  ${BLUEPRINT_PYTHON_DIR}/test
)

