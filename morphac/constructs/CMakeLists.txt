set(CONSTRUCTS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CONSTRUCTS_SRC_DIR ${CONSTRUCTS_DIR}/src)
set(CONSTRUCTS_INCLUDE_DIR ${CONSTRUCTS_DIR}/include)
set(CONSTRUCTS_TEST_DIR ${CONSTRUCTS_DIR}/test)
set(CONSTRUCTS_BINDING_DIR ${CONSTRUCTS_DIR}/binding)
set(CONSTRUCTS_BINDING_INCLUDE_DIR ${CONSTRUCTS_BINDING_DIR}/include)
set(CONSTRUCTS_BINDING_SRC_DIR ${CONSTRUCTS_BINDING_DIR}/src)
set(CONSTRUCTS_BINARY_DIR ${MORPHAC_BINARY_DIR}/constructs)
set(CONSTRUCTS_BINDING_BINARY_DIR ${CONSTRUCTS_BINARY_DIR}/binding)

# Adding subdirectories
# -------------------------------------------------

add_subdirectory(binding)


# Libraries
# -------------------------------------------------

# Constructs source files.
set(CONSTRUCTS_SRC

  coordinate2D.cc
  pose.cc
  velocity.cc
  control_input.cc
  state.cc
)

foreach(file ${CONSTRUCTS_SRC})
  get_filename_component(lib_name ${file} NAME_WE)
  set(header_name ${lib_name}.h)

  add_library(${lib_name} SHARED ${CONSTRUCTS_SRC_DIR}/${file} ${CONSTRUCTS_INCLUDE_DIR}/${header_name})
  target_include_directories(${lib_name} PRIVATE ${CONSTRUCTS_INCLUDE_DIR})
endforeach()

# Adding library dependencies.
target_link_libraries(state pose velocity)

# Tests
# -------------------------------------------------

# Constructs tests source files.
set(CONSTRUCTS_TEST_SRC

  coordinate2D_test.cc
  pose_test.cc
  velocity_test.cc
  control_input_test.cc
  state_test.cc
)

# Creating the test executables.
foreach(file ${CONSTRUCTS_TEST_SRC})
  get_filename_component(test_name ${file} NAME_WE)

  add_executable(${test_name} ${CONSTRUCTS_TEST_DIR}/${file})
  add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

# Linking depending libraries.
target_link_libraries(coordinate2D_test gtest_main coordinate2D)
target_link_libraries(pose_test gtest_main pose)
target_link_libraries(velocity_test gtest_main velocity)
target_link_libraries(control_input_test gtest_main control_input)
target_link_libraries(state_test gtest_main state)

