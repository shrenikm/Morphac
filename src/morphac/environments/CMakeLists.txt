# Adding libraries
add_library(environment2D ${CMAKE_CURRENT_SOURCE_DIR}/src/environment2D.cc)

# Adding test executables
add_executable(environment2D_test ${CMAKE_CURRENT_SOURCE_DIR}/test/environment2D_test.cc)
target_link_libraries(environment2D_test gtest_main environment2D)
add_test(NAME environment2D_test COMMAND environment2D_test)
