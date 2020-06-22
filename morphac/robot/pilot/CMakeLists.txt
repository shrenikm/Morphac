# Directories
# -------------------------------------------------

set(PILOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PILOT_SRC_DIR ${PILOT_DIR}/src)
set(PILOT_INCLUDE_DIR ${PILOT_DIR}/include)
set(PILOT_TEST_DIR ${PILOT_DIR}/test)

set(PILOT_BINARY_DIR ${ROBOT_BINARY_DIR}/pilot)

set(PILOT_BINDING_DIR ${PILOT_DIR}/binding)
set(PILOT_BINDING_INCLUDE_DIR ${PILOT_BINDING_DIR}/include)
set(PILOT_BINDING_SRC_DIR ${PILOT_BINDING_DIR}/src)
set(PILOT_BINDING_BINARY_DIR ${PILOT_BINARY_DIR}/binding)
set(PILOT_BINDING_INSTALL_DIR ${ROBOT_BINDING_INSTALL_DIR}/pilot)


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(binding)

# Libraries
# -------------------------------------------------

# Blueprint source files.
set(PILOT_SRC

  pilot.cc
)

foreach(file ${PILOT_SRC})
  get_filename_component(lib_name
    ${file} NAME_WE
  )

  get_header_name(header_name ${file})

  add_library(${lib_name}
    SHARED
    ${PILOT_SRC_DIR}/${file}
    ${PILOT_INCLUDE_DIR}/${header_name}
  )

  target_include_directories(${lib_name}
    PUBLIC
    ${PILOT_INCLUDE_DIR}
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

## Blueprint tests source files.
#set(PILOT_TEST_SRC
#
#  pilot_test.cc
#)
#
## Creating the test executables.
#foreach(file ${PILOT_TEST_SRC})
#  get_filename_component(test_name
#    ${file} NAME_WE
#  )
#
#  add_executable(
#    ${test_name}
#    ${PILOT_TEST_DIR}/${file}
#  )
#
#  add_test(NAME ${test_name}
#    COMMAND ${test_name}
#  )
#endforeach()
#
## Linking depending libraries.
#target_link_libraries(pilot_test
#  PUBLIC
#)
