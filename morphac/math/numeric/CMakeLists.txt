# Directories
# -------------------------------------------------

set(NUMERIC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(NUMERIC_SRC_DIR ${NUMERIC_DIR}/src)
set(NUMERIC_INCLUDE_DIR ${NUMERIC_DIR}/include)
set(NUMERIC_TEST_DIR ${NUMERIC_DIR}/test)
set(NUMERIC_PYTHON_DIR ${NUMERIC_DIR}/python)

set(NUMERIC_BINARY_DIR ${MATH_BINARY_DIR}/numeric)

set(NUMERIC_BINDING_DIR ${NUMERIC_DIR}/binding)
set(NUMERIC_BINDING_INCLUDE_DIR ${NUMERIC_BINDING_DIR}/include)
set(NUMERIC_BINDING_SRC_DIR ${NUMERIC_BINDING_DIR}/src)
set(NUMERIC_BINDING_BINARY_DIR ${NUMERIC_BINARY_DIR}/binding)

# Directories to install the bindings to.
set(NUMERIC_PACKAGE_DIR
  ${MATH_PACKAGE_DIR}/numeric
)
set(NUMERIC_SITE_PACKAGES_DIR
  ${MATH_SITE_PACKAGES_DIR}/numeric
)


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(binding)


# Libraries
# -------------------------------------------------

# Numeric source files.
set(NUMERIC_SRC

  integrator.cc
  euler_integrator.cc
  mid_point_integrator.cc
  rk4_integrator.cc
)

morphac_add_libraries(
  ${NUMERIC_INCLUDE_DIR}
  ${NUMERIC_SRC_DIR}
  ${NUMERIC_SRC}
)

# Adding library dependencies.
morphac_link_libraries(integrator
  kinematic_model
  state
  control_input
)

morphac_link_libraries(euler_integrator
  integrator
  kinematic_model
  state
  control_input
)

morphac_link_libraries(mid_point_integrator
  integrator
  kinematic_model
  state
  control_input
)

morphac_link_libraries(rk4_integrator
  integrator
  kinematic_model
  state
  control_input
)


# Tests
# -------------------------------------------------

# Numeric test source files.
set(NUMERIC_TEST_SRC

  integrator_test.cc
  integrator_type_test.cc
  euler_integrator_test.cc
  mid_point_integrator_test.cc
  rk4_integrator_test.cc
)

# Creating the test executables.
foreach(file ${NUMERIC_TEST_SRC})
  get_filename_component(test_name
    ${file} NAME_WE
  )

  add_executable(
    ${test_name}
    ${NUMERIC_TEST_DIR}/${file}
  )

  add_test(NAME ${test_name}
    COMMAND ${test_name}
  )
endforeach()

# Linking depending libraries.
target_link_libraries(integrator_test
  PUBLIC
  gtest_main
  integrator
  diffdrive_model
)

target_link_libraries(integrator_type_test
  PUBLIC
  gtest_main
  integrator
)

target_link_libraries(euler_integrator_test
  PUBLIC
  gtest_main
  euler_integrator
  diffdrive_model
)

target_link_libraries(mid_point_integrator_test
  PUBLIC
  gtest_main
  mid_point_integrator
  diffdrive_model
)

target_link_libraries(rk4_integrator_test
  PUBLIC
  gtest_main
  rk4_integrator
  diffdrive_model
)


# Installing
# -------------------------------------------------

# Install tests.
morphac_package_python_tests(
  ${MORPHAC_PACKAGE_UNIT_TEST_DIR}
  ${MORPHAC_SITE_PACKAGES_UNIT_TEST_DIR}
  ${NUMERIC_PYTHON_DIR}/test
)
