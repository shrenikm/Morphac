# Directories
# -------------------------------------------------

set(DRIVER_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(DRIVER_SRC_DIR ${DRIVER_DIR}/src)
set(DRIVER_INCLUDE_DIR ${DRIVER_DIR}/include)
set(DRIVER_TEST_DIR ${DRIVER_DIR}/test)

set(DRIVER_BINARY_DIR ${ROBOT_BINARY_DIR}/driver)

set(DRIVER_BINDING_DIR ${DRIVER_DIR}/binding)
set(DRIVER_BINDING_INCLUDE_DIR ${DRIVER_BINDING_DIR}/include)
set(DRIVER_BINDING_SRC_DIR ${DRIVER_BINDING_DIR}/src)
set(DRIVER_BINDING_BINARY_DIR ${DRIVER_BINARY_DIR}/binding)
set(DRIVER_BINDING_INSTALL_DIR ${ROBOT_BINDING_INSTALL_DIR}/driver)


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(binding)

# Libraries
# -------------------------------------------------

# Driver source files.
set(DRIVER_SRC

  pilot.cc
)

foreach(file ${DRIVER_SRC})
  get_filename_component(lib_name
    ${file} NAME_WE
  )

  get_header_name(header_name ${file})

  add_library(${lib_name}
    SHARED
    ${DRIVER_SRC_DIR}/${file}
    ${DRIVER_INCLUDE_DIR}/${header_name}
  )

  target_include_directories(${lib_name}
    PUBLIC
    ${DRIVER_INCLUDE_DIR}
  )
endforeach()

# Adding library dependencies.
target_link_libraries(pilot
  PUBLIC
  input
  playground_state
)


# Tests
# -------------------------------------------------

# Driver tests source files.
set(DRIVER_TEST_SRC

  pilot_test.cc
)

# Creating the test executables.
foreach(file ${DRIVER_TEST_SRC})
  get_filename_component(test_name
    ${file} NAME_WE
  )

  add_executable(
    ${test_name}
    ${DRIVER_TEST_DIR}/${file}
  )

  add_test(NAME ${test_name}
    COMMAND ${test_name}
  )
endforeach()

# Linking depending libraries.
target_link_libraries(pilot_test
  PUBLIC
  gtest
  pilot
)
