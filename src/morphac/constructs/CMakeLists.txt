set(CONSTRUCTS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CONSTRUCTS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CONSTRUCTS_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(CONSTRUCTS_BINDINGS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bindings)

# Constructs source files that can be built independently.
# These are the constructs' base libraries.
set(CONSTRUCTS_BASE_SRC

  coordinate2D.cc
  pose.cc
  velocity.cc
  control_input.cc
)

foreach(file ${CONSTRUCTS_BASE_SRC})
  get_filename_component(lib_name ${file} NAME_WE)
  set(header_name ${lib_name}.h)

  add_library(${lib_name} SHARED ${CONSTRUCTS_SRC_DIR}/${file} ${CONSTRUCTS_INCLUDE_DIR}/${header_name})
  target_include_directories(${lib_name} PRIVATE ${CONSTRUCTS_INCLUDE_DIR})
endforeach()

# Adding the state library. It depends on  pose and velocity.
add_library(state SHARED ${CONSTRUCTS_SRC_DIR}/state.cc ${CONSTRUCTS_INCLUDE_DIR}/state.h)
target_include_directories(state PRIVATE ${CONSTRUCTS_INCLUDE_DIR})
target_link_libraries(state pose velocity)

# Adding test executables
set(CONSTRUCTS_TEST_SRC

  coordinate2D_test.cc
  pose_test.cc
  velocity_test.cc
  control_input_test.cc
  state_test.cc
)

# Creating the test executables
foreach(file ${CONSTRUCTS_TEST_SRC})
  get_filename_component(exec_name ${file} NAME_WE)
  add_executable(${exec_name} ${CONSTRUCTS_TEST_DIR}/${file})
endforeach()

# Linking depending libraries
target_link_libraries(coordinate2D_test gtest_main coordinate2D)
target_link_libraries(pose_test gtest_main pose)
target_link_libraries(velocity_test gtest_main velocity)
target_link_libraries(control_input_test gtest_main control_input)
target_link_libraries(state_test gtest_main state)

# Adding tests
foreach(file ${CONSTRUCTS_TEST_SRC})
  get_filename_component(test_name ${file} NAME_WE)
  add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

