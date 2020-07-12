# Directories
# -------------------------------------------------

set(CONTROLLERS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CONTROLLERS_SRC_DIR ${CONTROLLERS_DIR}/src)
set(CONTROLLERS_INCLUDE_DIR ${CONTROLLERS_DIR}/include)
set(CONTROLLERS_TEST_DIR ${CONTROLLERS_DIR}/test)
set(CONTROLLERS_PYTHON_DIR ${CONTROLLERS_DIR}/python)

set(CONTROLLERS_BINARY_DIR ${MORPHAC_BINARY_DIR}/controllers)

set(CONTROLLERS_BINDING_DIR ${CONTROLLERS_DIR}/binding)
set(CONTROLLERS_BINDING_INCLUDE_DIR ${CONTROLLERS_BINDING_DIR}/include)
set(CONTROLLERS_BINDING_SRC_DIR ${CONTROLLERS_BINDING_DIR}/src)
set(CONTROLLERS_BINDING_BINARY_DIR ${CONTROLLERS_BINARY_DIR}/binding)
set(CONTROLLERS_BINDING_INSTALL_DIR
  ${PYTHON_BINDING_INSTALL_DIR}/controllers
)

# Adding subdirectories
# -------------------------------------------------

add_subdirectory(binding)


# Libraries
# -------------------------------------------------

# Constructs source files.
set(CONTROLLERS_SRC

  controller.cc
)

foreach(file ${CONTROLLERS_SRC})
  get_filename_component(lib_name
    ${file} NAME_WE
  )

  get_header_name(header_name ${file})

  add_library(${lib_name}
    SHARED
    ${CONTROLLERS_SRC_DIR}/${file}
    ${CONTROLLERS_INCLUDE_DIR}/${header_name}
  )

  target_include_directories(${lib_name}
    PUBLIC
    ${CONTROLLERS_INCLUDE_DIR}
  )
endforeach()


# Tests
# -------------------------------------------------

# Simulation tests source files.
set(CONTROLLERS_TEST_SRC

  controller_test.cc
)

# Creating the test executables.
foreach(file ${CONTROLLERS_TEST_SRC})
  get_filename_component(test_name
    ${file} NAME_WE
  )

  add_executable(
    ${test_name}
    ${CONTROLLERS_TEST_DIR}/${file}
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
