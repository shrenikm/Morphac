# Directories
# -------------------------------------------------

set(GEOMETRY_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(GEOMETRY_SRC_DIR ${GEOMETRY_DIR}/src)
set(GEOMETRY_INCLUDE_DIR ${GEOMETRY_DIR}/include)
set(GEOMETRY_TEST_DIR ${GEOMETRY_DIR}/test)
set(GEOMETRY_PYTHON_DIR ${GEOMETRY_DIR}/python)

set(GEOMETRY_BINARY_DIR ${MATH_BINARY_DIR}/geometry)

set(GEOMETRY_BINDING_DIR ${GEOMETRY_DIR}/binding)
set(GEOMETRY_BINDING_INCLUDE_DIR ${GEOMETRY_BINDING_DIR}/include)
set(GEOMETRY_BINDING_SRC_DIR ${GEOMETRY_BINDING_DIR}/src)
set(GEOMETRY_BINDING_BINARY_DIR ${GEOMETRY_BINARY_DIR}/binding)

# Directories to install the bindings to.
set(GEOMETRY_PACKAGE_DIR
  ${MATH_PACKAGE_DIR}/geometry
)
set(GEOMETRY_SITE_PACKAGES_DIR
  ${MATH_SITE_PACKAGES_DIR}/geometry
)


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(binding)


# Libraries
# -------------------------------------------------

# Geometry source files.
set(GEOMETRY_SRC

  lines.cc
  polygons.cc
  shapes.cc
)

morphac_add_libraries(
  ${GEOMETRY_INCLUDE_DIR}
  ${GEOMETRY_SRC_DIR}
  ${GEOMETRY_SRC}
)

# Adding library dependencies.
morphac_link_libraries(lines
  TRUE
  numeric_utils
)

morphac_link_libraries(polygons
  TRUE
  points_utils
  transforms
)

morphac_link_libraries(shapes
  TRUE
  numeric_utils
)


# Tests
# -------------------------------------------------

# Geometry test source files.
set(GEOMETRY_TEST_SRC

  lines_test.cc
  polygons_test.cc
  shapes_test.cc
)

# Creating the test executables.
foreach(file ${GEOMETRY_TEST_SRC})
  get_filename_component(test_name
    ${file} NAME_WE
  )

  add_executable(
    ${test_name}
    ${GEOMETRY_TEST_DIR}/${file}
  )

  add_test(NAME ${test_name}
    COMMAND ${test_name}
  )
endforeach()

# Linking depending libraries.
target_link_libraries(lines_test
  PUBLIC
  gtest_main
  lines
)

target_link_libraries(polygons_test
  PUBLIC
  gtest_main
  lines
  numeric_utils
  polygons
)

target_link_libraries(shapes_test
  PUBLIC
  gtest_main
  numeric_utils
  shapes
)


# Installing
# -------------------------------------------------

# Install tests.
morphac_package_python_tests(
  ${MORPHAC_PACKAGE_UNIT_TEST_DIR}
  ${MORPHAC_SITE_PACKAGES_UNIT_TEST_DIR}
  ${GEOMETRY_PYTHON_DIR}/test
)
