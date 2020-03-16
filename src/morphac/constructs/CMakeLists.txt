set(CONSTRUCTS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CONSTRUCTS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CONSTRUCTS_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(CONSTRUCTS_BINDING_DIR ${CMAKE_CURRENT_SOURCE_DIR}/binding)

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


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(binding)
