# Directories
# -------------------------------------------------

set(TRANSFORMS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(TRANSFORMS_SRC_DIR ${TRANSFORMS_DIR}/src)
set(TRANSFORMS_INCLUDE_DIR ${TRANSFORMS_DIR}/include)
set(TRANSFORMS_TEST_DIR ${TRANSFORMS_DIR}/test)
set(TRANSFORMS_PYTHON_DIR ${TRANSFORMS_DIR}/python)

set(TRANSFORMS_BINARY_DIR ${MATH_BINARY_DIR}/transforms)

set(TRANSFORMS_BINDING_DIR ${TRANSFORMS_DIR}/binding)
set(TRANSFORMS_BINDING_INCLUDE_DIR ${TRANSFORMS_BINDING_DIR}/include)
set(TRANSFORMS_BINDING_SRC_DIR ${TRANSFORMS_BINDING_DIR}/src)
set(TRANSFORMS_BINDING_BINARY_DIR ${TRANSFORMS_BINARY_DIR}/binding)
set(TRANSFORMS_BINDING_INSTALL_DIR
  ${MATH_BINDING_INSTALL_DIR}/transforms
)


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(binding)


# Libraries
# -------------------------------------------------

# Transforms source files.
set(TRANSFORMS_SRC

  transforms.cc
)

morphac_add_libraries(
  ${TRANSFORMS_INCLUDE_DIR}
  ${TRANSFORMS_SRC_DIR}
  ${TRANSFORMS_SRC}
)

# Adding library dependencies.
morphac_link_libraries(transforms
  points_utils
)


# Tests
# -------------------------------------------------

# Transforms test source files.
set(TRANSFORMS_TEST_SRC

  transforms_test.cc
)

# Creating the test executables.
foreach(file ${TRANSFORMS_TEST_SRC})
  get_filename_component(test_name
    ${file} NAME_WE
  )

  add_executable(
    ${test_name}
    ${TRANSFORMS_TEST_DIR}/${file}
  )

  add_test(NAME ${test_name}
    COMMAND ${test_name}
  )
endforeach()

# Linking depending libraries.
target_link_libraries(transforms_test
  PUBLIC
  gtest_main
  transforms
)
