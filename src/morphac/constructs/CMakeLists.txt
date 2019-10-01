# Adding libraries
add_library(coordinate ${CMAKE_CURRENT_SOURCE_DIR}/src/coordinate.cc)
add_library(pose ${CMAKE_CURRENT_SOURCE_DIR}/src/pose.cc)

# Adding test executables
add_executable(coordinate_test ${CMAKE_CURRENT_SOURCE_DIR}/test/coordinate_test.cc)
target_link_libraries(coordinate_test gtest_main)
target_link_libraries(coordinate_test coordinate)
add_test(NAME coordinate_test COMMAND coordinate_test)
