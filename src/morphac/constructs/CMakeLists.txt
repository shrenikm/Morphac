# Adding libraries
add_library(coordinate ${CMAKE_CURRENT_SOURCE_DIR}/src/coordinate.cc)
add_library(pose ${CMAKE_CURRENT_SOURCE_DIR}/src/pose.cc)
add_library(velocity ${CMAKE_CURRENT_SOURCE_DIR}/src/velocity.cc)
add_library(control_input ${CMAKE_CURRENT_SOURCE_DIR}/src/control_input.cc)

add_library(state ${CMAKE_CURRENT_SOURCE_DIR}/src/state.cc)
target_link_libraries(state pose velocity)

# Adding test executables
# Coordinate test
add_executable(coordinate_test ${CMAKE_CURRENT_SOURCE_DIR}/test/coordinate_test.cc)
target_link_libraries(coordinate_test gtest_main coordinate)
add_test(NAME coordinate_test COMMAND coordinate_test)

# Pose test
add_executable(pose_test ${CMAKE_CURRENT_SOURCE_DIR}/test/pose_test.cc)
target_link_libraries(pose_test gtest_main pose)
add_test(NAME pose_test COMMAND pose_test)

# Velocity test
add_executable(velocity_test ${CMAKE_CURRENT_SOURCE_DIR}/test/velocity_test.cc)
target_link_libraries(velocity_test gtest_main velocity)
add_test(NAME velocity_test COMMAND velocity_test)

# Control input test
add_executable(control_input_test ${CMAKE_CURRENT_SOURCE_DIR}/test/control_input_test.cc)
target_link_libraries(control_input_test gtest_main control_input)
add_test(NAME control_input_test COMMAND control_input_test)

# State test
add_executable(state_test ${CMAKE_CURRENT_SOURCE_DIR}/test/state_test.cc)
target_link_libraries(state_test gtest_main state)
add_test(NAME state_test COMMAND state_test)

