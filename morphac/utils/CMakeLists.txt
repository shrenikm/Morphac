# Directories
# -------------------------------------------------

set(UTILS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(UTILS_SRC_DIR ${UTILS_DIR}/src)
set(UTILS_INCLUDE_DIR ${UTILS_DIR}/include)
set(UTILS_TEST_DIR ${UTILS_DIR}/test)

set(UTILS_BINARY_DIR ${MORPHAC_BINARY_DIR}/utils)

set(UTILS_BINDING_DIR ${UTILS_DIR}/binding)
set(UTILS_BINDING_INCLUDE_DIR ${UTILS_BINDING_DIR}/include)
set(UTILS_BINDING_SRC_DIR ${UTILS_BINDING_DIR}/src)
set(UTILS_BINDING_BINARY_DIR ${UTILS_BINARY_DIR}/binding)
set(UTILS_BINDING_INSTALL_DIR
  ${PYTHON_BINDING_INSTALL_DIR}/utils
)


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(binding)


# Libraries
# -------------------------------------------------

# Utils source files.
set(UTILS_SRC

  angle_utils.cc
)

foreach(file ${UTILS_SRC})
  get_filename_component(lib_name
    ${file} NAME_WE
  )

  get_header_name(header_name ${file})

  add_library(${lib_name}
    SHARED
    ${UTILS_SRC_DIR}/${file}
    ${UTILS_INCLUDE_DIR}/${header_name}
  )

  target_include_directories(${lib_name}
    PUBLIC
    ${UTILS_INCLUDE_DIR}
  )
endforeach()


# Tests
# -------------------------------------------------

# Utils test source files.
set(UTILS_TEST_SRC

  angle_utils_test.cc
)

# Creating the test executables.
foreach(file ${UTILS_TEST_SRC})
  get_filename_component(test_name
    ${file} NAME_WE
  )

  add_executable(
    ${test_name}
    ${UTILS_TEST_DIR}/${file}
  )

  add_test(NAME ${test_name}
    COMMAND ${test_name}
  )
endforeach()

# Linking depending libraries.
target_link_libraries(angle_utils_test
  PUBLIC
  gtest_main angle_utils
)


