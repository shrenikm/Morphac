# Directories
# -------------------------------------------------

set(PLANNERS_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PLANNERS_BASE_SRC_DIR ${PLANNERS_BASE_DIR}/src)
set(PLANNERS_BASE_INCLUDE_DIR ${PLANNERS_BASE_DIR}/include)
set(PLANNERS_BASE_TEST_DIR ${PLANNERS_BASE_DIR}/test)
set(PLANNERS_BASE_PYTHON_DIR ${PLANNERS_BASE_DIR}/python)

set(PLANNERS_BASE_BINARY_DIR ${PLANNERS_BINARY_DIR}/base)

set(PLANNERS_BASE_BINDING_DIR ${PLANNERS_BASE_DIR}/binding)
set(PLANNERS_BASE_BINDING_INCLUDE_DIR ${PLANNERS_BASE_BINDING_DIR}/include)
set(PLANNERS_BASE_BINDING_SRC_DIR ${PLANNERS_BASE_BINDING_DIR}/src)
set(PLANNERS_BASE_BINDING_BINARY_DIR ${PLANNERS_BASE_BINARY_DIR}/binding)
set(PLANNERS_BASE_BINDING_INSTALL_DIR
  ${PLANNERS_BINDING_INSTALL_DIR}/base
)

# Directories to install the bindings to.
set(PLANNERS_BASE_PACKAGE_DIR
  ${PLANNERS_PACKAGE_DIR}/base
)
set(PLANNERS_BASE_SITE_PACKAGES_DIR
  ${PLANNERS_SITE_PACKAGES_DIR}/base
)

# Adding subdirectories
# -------------------------------------------------

add_subdirectory(binding)


# Libraries
# -------------------------------------------------

# Planners base source files.
set(PLANNERS_BASE_SRC

  planner.cc
)

morphac_add_libraries(
  ${PLANNERS_BASE_INCLUDE_DIR}
  ${PLANNERS_BASE_SRC_DIR}
  ${PLANNERS_BASE_SRC}
)


# Tests
# -------------------------------------------------

# Planners base tests source files.
set(PLANNERS_BASE_TEST_SRC

  planner_test.cc
)

# Creating the test executables.
foreach(file ${PLANNERS_BASE_TEST_SRC})
  get_filename_component(test_name
    ${file} NAME_WE
  )

  add_executable(
    ${test_name}
    ${PLANNERS_BASE_TEST_DIR}/${file}
  )

  add_test(NAME ${test_name}
    COMMAND ${test_name}
  )
endforeach()

# Linking depending libraries.
target_link_libraries(planner_test
  PUBLIC
  gtest_main
  trajectory
  planner
)


# Installing
# -------------------------------------------------

# Install tests.
morphac_package_python_tests(
  ${MORPHAC_PACKAGE_UNIT_TEST_DIR}
  ${MORPHAC_SITE_PACKAGES_UNIT_TEST_DIR}
  ${PLANNERS_BASE_PYTHON_DIR}/test
)
