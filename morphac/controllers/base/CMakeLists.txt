# Directories
# -------------------------------------------------

set(CONTROLLERS_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CONTROLLERS_BASE_SRC_DIR ${CONTROLLERS_BASE_DIR}/src)
set(CONTROLLERS_BASE_INCLUDE_DIR ${CONTROLLERS_BASE_DIR}/include)
set(CONTROLLERS_BASE_TEST_DIR ${CONTROLLERS_BASE_DIR}/test)
set(CONTROLLERS_BASE_PYTHON_DIR ${CONTROLLERS_BASE_DIR}/python)

set(CONTROLLERS_BASE_BINARY_DIR ${CONTROLLERS_BINARY_DIR}/controllers)

set(CONTROLLERS_BASE_BINDING_DIR ${CONTROLLERS_BASE_DIR}/binding)
set(CONTROLLERS_BASE_BINDING_INCLUDE_DIR ${CONTROLLERS_BASE_BINDING_DIR}/include)
set(CONTROLLERS_BASE_BINDING_SRC_DIR ${CONTROLLERS_BASE_BINDING_DIR}/src)
set(CONTROLLERS_BASE_BINDING_BINARY_DIR ${CONTROLLERS_BASE_BINARY_DIR}/binding)
set(CONTROLLERS_BASE_BINDING_INSTALL_DIR
  ${CONTROLLERS_BINDING_INSTALL_DIR}/base
)

# Adding subdirectories
# -------------------------------------------------

add_subdirectory(binding)


# Libraries
# -------------------------------------------------

# Constructs source files.
set(CONTROLLERS_BASE_SRC

  controller.cc
)

foreach(file ${CONTROLLERS_BASE_SRC})
  get_filename_component(lib_name
    ${file} NAME_WE
  )

  get_header_name(header_name ${file})

  add_library(${lib_name}
    SHARED
    ${CONTROLLERS_BASE_SRC_DIR}/${file}
    ${CONTROLLERS_BASE_INCLUDE_DIR}/${header_name}
  )

  target_include_directories(${lib_name}
    PUBLIC
    ${CONTROLLERS_BASE_INCLUDE_DIR}
  )
endforeach()


# Tests
# -------------------------------------------------

# Simulation tests source files.
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
