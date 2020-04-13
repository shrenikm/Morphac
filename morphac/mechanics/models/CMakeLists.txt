# Directories
# -------------------------------------------------

set(MODELS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(MODELS_SRC_DIR ${MODELS_DIR}/src)
set(MODELS_INCLUDE_DIR ${MODELS_DIR}/include)
set(MODELS_TEST_DIR ${MODELS_DIR}/test)
set(MODELS_BINDING_DIR ${MODELS_DIR}/binding)
set(MODELS_BINDING_INCLUDE_DIR ${MODELS_BINDING_DIR}/include)
set(MODELS_BINDING_SRC_DIR ${MODELS_BINDING_DIR}/src)
set(MODELS_BINARY_DIR ${MECHANICS_BINARY_DIR}/models)
set(MODELS_BINDING_BINARY_DIR ${MODELS_BINARY_DIR}/binding)
set(MODELS_BINDING_INSTALL_DIR
  ${MECHANICS_BINDING_INSTALL_DIR}/models
)


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(binding)


# Libraries
# -------------------------------------------------

# Models source files.
set(MODELS_SRC

  kinematic_model.cc
  dubin_model.cc
  diffdrive_model.cc
  tricycle_model.cc
)

foreach(file ${MODELS_SRC})
  get_filename_component(lib_name
    ${file} NAME_WE
  )

  get_header_name(header_name ${file})

  add_library(${lib_name}
    SHARED
    ${MODELS_SRC_DIR}/${file}
    ${MODELS_INCLUDE_DIR}/${header_name}
  )
  target_include_directories(${lib_name}
    PUBLIC
    ${MODELS_INCLUDE_DIR}
  )
endforeach()

# Adding library dependencies.
target_link_libraries(kinematic_model
  PUBLIC
  state input
)
target_link_libraries(dubin_model
  PUBLIC
  kinematic_model state input
)
target_link_libraries(diffdrive_model
  PUBLIC
  kinematic_model state input
)
target_link_libraries(tricycle_model
  PUBLIC
  kinematic_model state input
)

# Tests
# -------------------------------------------------

# Models test source files.
set(MODELS_TEST_SRC

  kinematic_model_test.cc
  dubin_model_test.cc
  diffdrive_model_test.cc
  tricycle_model_test.cc
)

# Creating the test executables.
foreach(file ${MODELS_TEST_SRC})
  get_filename_component(test_name
    ${file} NAME_WE
  )

  add_executable(
    ${test_name}
    ${MODELS_TEST_DIR}/${file}
  )
  add_test(NAME ${test_name}
    COMMAND ${test_name}
  )
endforeach()

# Linking depending libraries.
target_link_libraries(kinematic_model_test
  PUBLIC
  gtest_main kinematic_model
)
target_link_libraries(dubin_model_test
  PUBLIC
  gtest_main dubin_model
)
target_link_libraries(diffdrive_model_test
  PUBLIC
  gtest_main diffdrive_model
)
target_link_libraries(tricycle_model_test
  PUBLIC
  gtest_main tricycle_model
)

