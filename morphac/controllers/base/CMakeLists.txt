# Directories
# -------------------------------------------------

set(CONTROLLERS_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CONTROLLERS_BASE_SRC_DIR ${CONTROLLERS_BASE_DIR}/src)
set(CONTROLLERS_BASE_INCLUDE_DIR ${CONTROLLERS_BASE_DIR}/include)
set(CONTROLLERS_BASE_TEST_DIR ${CONTROLLERS_BASE_DIR}/test)
set(CONTROLLERS_BASE_PYTHON_DIR ${CONTROLLERS_BASE_DIR}/python)

set(CONTROLLERS_BASE_BINARY_DIR ${CONTROLLERS_BINARY_DIR}/base)

set(CONTROLLERS_BASE_BINDING_DIR ${CONTROLLERS_BASE_DIR}/binding)
set(CONTROLLERS_BASE_BINDING_INCLUDE_DIR ${CONTROLLERS_BASE_BINDING_DIR}/include)
set(CONTROLLERS_BASE_BINDING_SRC_DIR ${CONTROLLERS_BASE_BINDING_DIR}/src)
set(CONTROLLERS_BASE_BINDING_BINARY_DIR ${CONTROLLERS_BASE_BINARY_DIR}/binding)

# Directories to install the bindings to.
set(CONTROLLERS_BASE_PACKAGES_INSTALL_DIR
  ${CONTROLLERS_PACKAGES_INSTALL_DIR}/base
)
set(CONTROLLERS_BASE_SITE_PACKAGES_INSTALL_DIR
  ${CONTROLLERS_SITE_PACKAGES_INSTALL_DIR}/base
)

# Adding subdirectories
# -------------------------------------------------

add_subdirectory(binding)


# Libraries
# -------------------------------------------------

# Controllers base source files.
set(CONTROLLERS_BASE_SRC

  controller.cc
)

morphac_add_libraries(
  ${CONTROLLERS_BASE_INCLUDE_DIR}
  ${CONTROLLERS_BASE_SRC_DIR}
  ${CONTROLLERS_BASE_SRC}
)


# Tests
# -------------------------------------------------

# Controllers base tests source files.
set(CONTROLLERS_BASE_TEST_SRC

  controller_test.cc
)

# Creating the test executables.
foreach(file ${CONTROLLERS_BASE_TEST_SRC})
  get_filename_component(test_name
    ${file} NAME_WE
  )

  add_executable(
    ${test_name}
    ${CONTROLLERS_BASE_TEST_DIR}/${file}
  )

  add_test(NAME ${test_name}
    COMMAND ${test_name}
  )
endforeach()

# Linking depending libraries.
target_link_libraries(controller_test
  PUBLIC
  gtest_main
  control_input
  controller
)
