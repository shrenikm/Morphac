# Adding libraries
add_library(footprint2D ${CMAKE_CURRENT_SOURCE_DIR}/src/footprint2D.cc)

add_library(robot2D ${CMAKE_CURRENT_SOURCE_DIR}/src/robot2D.cc)
target_link_libraries(robot2D pose state velocity kinematic_model footprint2D)

# Robot2D test
add_executable(robot2D_test ${CMAKE_CURRENT_SOURCE_DIR}/test/robot2D_test.cc)
target_link_libraries(robot2D_test gtest_main robot2D)
add_test(NAME robot2D_test COMMAND robot2D_test)

# Footprint2D test
add_executable(footprint2D_test ${CMAKE_CURRENT_SOURCE_DIR}/test/footprint2D_test.cc)
target_link_libraries(footprint2D_test gtest_main footprint2D)
add_test(NAME footprint2D_test COMMAND footprint2D_test)

