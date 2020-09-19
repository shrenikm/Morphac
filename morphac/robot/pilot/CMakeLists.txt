# Directories
# -------------------------------------------------

set(PILOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PILOT_SRC_DIR ${PILOT_DIR}/src)
set(PILOT_INCLUDE_DIR ${PILOT_DIR}/include)
set(PILOT_TEST_DIR ${PILOT_DIR}/test)
set(PILOT_PYTHON_DIR ${PILOT_DIR}/python)

set(PILOT_BINARY_DIR ${ROBOT_BINARY_DIR}/pilot)

set(PILOT_BINDING_DIR ${PILOT_DIR}/binding)
set(PILOT_BINDING_INCLUDE_DIR ${PILOT_BINDING_DIR}/include)
set(PILOT_BINDING_SRC_DIR ${PILOT_BINDING_DIR}/src)
set(PILOT_BINDING_BINARY_DIR ${PILOT_BINARY_DIR}/binding)

set(PILOT_PACKAGE_DIR
  ${ROBOT_PACKAGE_DIR}/pilot
)
set(PILOT_SITE_PACKAGES_DIR
  ${ROBOT_SITE_PACKAGES_DIR}/pilot
)


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(binding)

# Libraries
# -------------------------------------------------

# Pilot source files.
set(PILOT_SRC

  pilot.cc
)

morphac_add_libraries(
  ${PILOT_INCLUDE_DIR}
  ${PILOT_SRC_DIR}
  ${PILOT_SRC}
)

# Adding library dependencies.
morphac_link_libraries(pilot
  control_input
  playground_state
)


# Tests
# -------------------------------------------------

# Pilot tests source files.
set(PILOT_TEST_SRC

  pilot_test.cc
)

# Creating the test executables.
foreach(file ${PILOT_TEST_SRC})
  get_filename_component(test_name
    ${file} NAME_WE
  )

  add_executable(
    ${test_name}
    ${PILOT_TEST_DIR}/${file}
  )

  add_test(NAME ${test_name}
    COMMAND ${test_name}
  )
endforeach()

# Linking depending libraries.
target_link_libraries(pilot_test
  PUBLIC
  gtest_main
  pilot
)


# Installing
# -------------------------------------------------

# Install tests.
morphac_package_python_tests(
  ${MORPHAC_PACKAGE_UNIT_TEST_DIR}
  ${MORPHAC_SITE_PACKAGES_UNIT_TEST_DIR}
  ${PILOT_PYTHON_DIR}/test
)
