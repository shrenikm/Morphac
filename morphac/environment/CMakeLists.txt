# Directories
# -------------------------------------------------

set(ENVIRONMENT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(ENVIRONMENT_SRC_DIR ${ENVIRONMENT_DIR}/src)
set(ENVIRONMENT_INCLUDE_DIR ${ENVIRONMENT_DIR}/include)
set(ENVIRONMENT_TEST_DIR ${ENVIRONMENT_DIR}/test)
set(ENVIRONMENT_PYTHON_DIR ${ENVIRONMENT_DIR}/python)

set(ENVIRONMENT_BINARY_DIR ${MORPHAC_BINARY_DIR}/environment)

set(ENVIRONMENT_BINDING_DIR ${ENVIRONMENT_DIR}/binding)
set(ENVIRONMENT_BINDING_INCLUDE_DIR ${ENVIRONMENT_BINDING_DIR}/include)
set(ENVIRONMENT_BINDING_SRC_DIR ${ENVIRONMENT_BINDING_DIR}/src)
set(ENVIRONMENT_BINDING_BINARY_DIR ${ENVIRONMENT_BINARY_DIR}/binding)
set(ENVIRONMENT_BINDING_INSTALL_DIR
  ${PYTHON_BINDING_INSTALL_DIR}/environment
)


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(binding)


# Libraries
# -------------------------------------------------

# Environment source files.
set(ENVIRONMENT_SRC

  map.cc
)

foreach(file ${ENVIRONMENT_SRC})
  get_filename_component(lib_name ${file} NAME_WE)
  get_header_name(header_name ${file})

  add_library(${lib_name}
    SHARED
    ${ENVIRONMENT_SRC_DIR}/${file}
    ${ENVIRONMENT_INCLUDE_DIR}/${header_name}
  )

  target_include_directories(${lib_name}
    PUBLIC
    ${ENVIRONMENT_INCLUDE_DIR}
  )
endforeach()


# Tests
# -------------------------------------------------

# Environment tests source files.
set(ENVIRONMENT_TEST_SRC

  map_test.cc
)

# Creating the test executables.
foreach(file ${ENVIRONMENT_TEST_SRC})
  get_filename_component(test_name
    ${file} NAME_WE
  )

  add_executable(
    ${test_name}
    ${ENVIRONMENT_TEST_DIR}/${file}
  )

  add_test(NAME ${test_name}
    COMMAND ${test_name}
  )
endforeach()

# Linking depending libraries.
target_link_libraries(map_test
  PUBLIC
  gtest_main
  map
)

