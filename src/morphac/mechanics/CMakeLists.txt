# Adding libraries
add_library(kinematic_model ${CMAKE_CURRENT_SOURCE_DIR}/src/kinematic_model.cc)
target_link_libraries(kinematic_model state control_input)

# Kinematic model test
add_executable(kinematic_model_test ${CMAKE_CURRENT_SOURCE_DIR}/test/kinematic_model_test.cc)
target_link_libraries(kinematic_model_test gtest_main kinematic_model)
add_test(NAME kinematic_model_test COMMAND kinematic_model_test)



