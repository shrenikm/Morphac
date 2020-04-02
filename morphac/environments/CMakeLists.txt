set(ENVIRONMENTS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(ENVIRONMENTS_SRC_DIR ${ENVIRONMENTS_DIR}/src)
set(ENVIRONMENTS_INCLUDE_DIR ${ENVIRONMENTS_DIR}/include)
set(ENVIRONMENTS_TEST_DIR ${ENVIRONMENTS_DIR}/test)
set(ENVIRONMENTS_BINDING_DIR ${ENVIRONMENTS_DIR}/binding)
set(ENVIRONMENTS_BINDING_INCLUDE_DIR ${ENVIRONMENTS_BINDING_DIR}/include)
set(ENVIRONMENTS_BINDING_SRC_DIR ${ENVIRONMENTS_BINDING_DIR}/src)
set(ENVIRONMENTS_BINARY_DIR ${MORPHAC_BINARY_DIR}/environments)
set(ENVIRONMENTS_BINDING_BINARY_DIR ${ENVIRONMENTS_BINARY_DIR}/binding)

# Adding subdirectories
# -------------------------------------------------

add_subdirectory(binding)


# Libraries
# -------------------------------------------------

# Environment source files.
set(ENVIRONMENT_SRC

  environment2D.cc
)

foreach(file ${ENVIRONMENT_SRC})
  get_filename_component(lib_name ${file} NAME_WE)
  set(header_name ${lib_name}.h)

  add_library(${lib_name} SHARED ${ENVIRONMENTS_SRC_DIR}/${file} ${ENVIRONMENTS_INCLUDE_DIR}/${header_name})
  target_include_directories(${lib_name} PRIVATE ${ENVIRONMENTS_INCLUDE_DIR})
endforeach()


# Tests
# -------------------------------------------------

# Environment tests source files.
set(ENVIRONMENT_TEST_SRC

  environment2D_test.cc
)

# Creating the test executables.
foreach(file ${ENVIRONMENT_TEST_SRC})
  get_filename_component(test_name ${file} NAME_WE)

  add_executable(${test_name} ${ENVIRONMENTS_TEST_DIR}/${file})
  add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

# Linking depending libraries.
target_link_libraries(environment2D_test gtest_main environment2D)

