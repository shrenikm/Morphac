# Adding libraries
add_library(coordinate ${CMAKE_CURRENT_SOURCE_DIR}/src/coordinate.cc)

# Adding test executables
add_executable(coordinate_test ${CMAKE_CURRENT_SOURCE_DIR}/test/coordinate_test.cc)
