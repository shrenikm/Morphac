# Adding libraries
add_library(kinematic_model ${CMAKE_CURRENT_SOURCE_DIR}/src/kinematic_model.cc)
target_link_libraries(kinematic_model state control_input)

add_library(dubin_model ${CMAKE_CURRENT_SOURCE_DIR}/src/dubin_model.cc)
target_link_libraries(dubin_model kinematic_model state control_input)

add_library(diffdrive_model ${CMAKE_CURRENT_SOURCE_DIR}/src/diffdrive_model.cc)
target_link_libraries(diffdrive_model kinematic_model state control_input)

# Adding test executables
# Kinematic model test
add_executable(kinematic_model_test ${CMAKE_CURRENT_SOURCE_DIR}/test/kinematic_model_test.cc)
target_link_libraries(kinematic_model_test gtest_main kinematic_model)
add_test(NAME kinematic_model_test COMMAND kinematic_model_test)

# Dubin model test
add_executable(dubin_model_test ${CMAKE_CURRENT_SOURCE_DIR}/test/dubin_model_test.cc)
target_link_libraries(dubin_model_test gtest_main dubin_model)
add_test(NAME dubin_model_test COMMAND dubin_model_test)

# Diffdrive model test
add_executable(diffdrive_model_test ${CMAKE_CURRENT_SOURCE_DIR}/test/diffdrive_model_test.cc)
target_link_libraries(diffdrive_model_test gtest_main diffdrive_model)
add_test(NAME diffdrive_model_test COMMAND diffdrive_model_test)






