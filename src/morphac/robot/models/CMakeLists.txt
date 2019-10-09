# Adding libraries
add_library(robot2D ${CMAKE_CURRENT_SOURCE_DIR}/src/robot2D.cc)
target_link_libraries(robot2D pose state velocity kinematic_model)

# Robot2D test
add_executable(robot2D_test ${CMAKE_CURRENT_SOURCE_DIR}/test/robot2D_test.cc)
target_link_libraries(robot2D_test gtest_main robot2D)
add_test(NAME robot2D_test COMMAND robot2D_test)
