# Directories
# -------------------------------------------------

set(MODELS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(MODELS_SRC_DIR ${MODELS_DIR}/src)
set(MODELS_INCLUDE_DIR ${MODELS_DIR}/include)
set(MODELS_TEST_DIR ${MODELS_DIR}/test)
set(MODELS_PYTHON_DIR ${MODELS_DIR}/python)

set(MODELS_BINARY_DIR ${MECHANICS_BINARY_DIR}/models)

set(MODELS_BINDING_DIR ${MODELS_DIR}/binding)
set(MODELS_BINDING_INCLUDE_DIR ${MODELS_BINDING_DIR}/include)
set(MODELS_BINDING_SRC_DIR ${MODELS_BINDING_DIR}/src)
set(MODELS_BINDING_BINARY_DIR ${MODELS_BINARY_DIR}/binding)

# Directories to install the bindings to.
set(MODELS_PACKAGE_DIR
  ${MECHANICS_PACKAGE_DIR}/models
)
set(MODELS_SITE_PACKAGES_DIR
  ${MECHANICS_SITE_PACKAGES_DIR}/models
)


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(binding)


# Libraries
# -------------------------------------------------

# Models source files.
set(MODELS_SRC

  kinematic_model.cc
  ackermann_model.cc
  diffdrive_model.cc
  dubin_model.cc
  tricycle_model.cc
)

morphac_add_libraries(
  ${MODELS_INCLUDE_DIR}
  ${MODELS_SRC_DIR}
  ${MODELS_SRC}
)

# Adding library dependencies.
morphac_link_libraries(kinematic_model
  state
  control_input
  footprint
)

morphac_link_libraries(ackermann_model
  kinematic_model
  mechanics_constants
  angle_utils
)

morphac_link_libraries(diffdrive_model
  kinematic_model
  mechanics_constants
  angle_utils
)

morphac_link_libraries(dubin_model
  kinematic_model
  mechanics_constants
  angle_utils
)

morphac_link_libraries(tricycle_model
  kinematic_model
  mechanics_constants
  angle_utils
)


# Tests
# -------------------------------------------------

# Models test source files.
set(MODELS_TEST_SRC

  kinematic_model_test.cc
  ackermann_model_test.cc
  diffdrive_model_test.cc
  dubin_model_test.cc
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

target_link_libraries(kinematic_model_test
  PUBLIC
  gtest_main
  kinematic_model
  numeric_utils
)

target_link_libraries(ackermann_model_test
  PUBLIC
  gtest_main
  ackermann_model
)

# Linking depending libraries.
target_link_libraries(tricycle_model_test
  PUBLIC
  gtest_main
  tricycle_model
)

target_link_libraries(diffdrive_model_test
  PUBLIC
  gtest_main
  diffdrive_model
)

target_link_libraries(dubin_model_test
  PUBLIC
  gtest_main
  dubin_model
)


# Installing
# -------------------------------------------------

# Install tests.
morphac_package_python_tests(
  ${MODELS_PACKAGE_DIR}/test
  ${MODELS_SITE_PACKAGES_DIR}/test
  ${MODELS_PYTHON_DIR}/test
)


