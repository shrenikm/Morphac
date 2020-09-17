# Directories
# -------------------------------------------------

set(CONTROLLERS_BASIC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CONTROLLERS_BASIC_SRC_DIR ${CONTROLLERS_BASIC_DIR}/src)
set(CONTROLLERS_BASIC_INCLUDE_DIR ${CONTROLLERS_BASIC_DIR}/include)
set(CONTROLLERS_BASIC_TEST_DIR ${CONTROLLERS_BASIC_DIR}/test)
set(CONTROLLERS_BASIC_PYTHON_DIR ${CONTROLLERS_BASIC_DIR}/python)

set(CONTROLLERS_BASIC_BINARY_DIR ${CONTROLLERS_BINARY_DIR}/basic)

set(CONTROLLERS_BASIC_BINDING_DIR ${CONTROLLERS_BASIC_DIR}/binding)
set(CONTROLLERS_BASIC_BINDING_INCLUDE_DIR ${CONTROLLERS_BASIC_BINDING_DIR}/include)
set(CONTROLLERS_BASIC_BINDING_SRC_DIR ${CONTROLLERS_BASIC_BINDING_DIR}/src)
set(CONTROLLERS_BASIC_BINDING_BINARY_DIR ${CONTROLLERS_BASIC_BINARY_DIR}/binding)
set(CONTROLLERS_BASIC_BINDING_INSTALL_DIR
  ${CONTROLLERS_BINDING_INSTALL_DIR}/basic
)

# Adding subdirectories
# -------------------------------------------------

add_subdirectory(binding)


# Libraries
# -------------------------------------------------

# Controllers basic source files.
set(CONTROLLERS_BASIC_SRC

  constant_controller.cc
  zero_controller.cc
)

morphac_add_libraries(
  ${CONTROLLERS_BASIC_INCLUDE_DIR}
  ${CONTROLLERS_BASIC_SRC_DIR}
  ${CONTROLLERS_BASIC_SRC}
)

# Adding library dependencies.
morphac_link_libraries(
  constant_controller
  control_input
  controller
)

morphac_link_libraries(
  zero_controller
  control_input
  controller
)


# Tests
# -------------------------------------------------

# Controllers basic tests source files.
set(CONTROLLERS_BASIC_TEST_SRC

  constant_controller_test.cc
  zero_controller_test.cc
)

# Creating the test executables.
foreach(file ${CONTROLLERS_BASIC_TEST_SRC})
  get_filename_component(test_name
    ${file} NAME_WE
  )

  add_executable(
    ${test_name}
    ${CONTROLLERS_BASIC_TEST_DIR}/${file}
  )

  add_test(NAME ${test_name}
    COMMAND ${test_name}
  )
endforeach()

# Linking depending libraries.
target_link_libraries(constant_controller_test
  PUBLIC
  gtest_main
  constant_controller
)

target_link_libraries(zero_controller_test
  PUBLIC
  gtest_main
  zero_controller
)
